#pragma once

#include "eFloatingPointKind.h"
#include "CAbsOperator.h"
#include <cstdint>
#include <string>
#include <fstream>

namespace ipgdlib
{
	namespace audio
	{

		enum eSampleRateKind : uint8_t { esrk8kHz, esrk11kHz, esrk22kHz, esrk44kHz, esrk48kHz, esrk96kHz, esrk192kHz };

		template <eSampleRateKind sampleRate>
		struct sample_rate_trait {};

		template <>
		struct sample_rate_trait<eSampleRateKind::esrk8kHz> { static constexpr size_t SAMPLE_PER_SECOND = 8000; };
		template <>
		struct sample_rate_trait<eSampleRateKind::esrk11kHz> { static constexpr size_t SAMPLE_PER_SECOND = 11025; };
		template <>
		struct sample_rate_trait<eSampleRateKind::esrk22kHz> { static constexpr size_t SAMPLE_PER_SECOND = 22050; };
		template <>
		struct sample_rate_trait<eSampleRateKind::esrk44kHz> { static constexpr size_t SAMPLE_PER_SECOND = 44100; };
		template <>
		struct sample_rate_trait<eSampleRateKind::esrk48kHz> { static constexpr size_t SAMPLE_PER_SECOND = 48000; };
		template <>
		struct sample_rate_trait<eSampleRateKind::esrk96kHz> { static constexpr size_t SAMPLE_PER_SECOND = 96000; };
		template <>
		struct sample_rate_trait<eSampleRateKind::esrk192kHz> { static constexpr size_t SAMPLE_PER_SECOND = 192000; };

		struct ISampleRateKind
		{
			virtual ~ISampleRateKind() {};
			virtual eSampleRateKind getSampleRateKind() const noexcept = 0;

			size_t getSampleRate() const noexcept
			{
				switch (this->getSampleRateKind())
				{
					case eSampleRateKind::esrk8kHz: return sample_rate_trait<eSampleRateKind::esrk8kHz>::SAMPLE_PER_SECOND;
					case eSampleRateKind::esrk11kHz: return sample_rate_trait<eSampleRateKind::esrk11kHz>::SAMPLE_PER_SECOND;
					case eSampleRateKind::esrk22kHz: return sample_rate_trait<eSampleRateKind::esrk22kHz>::SAMPLE_PER_SECOND;
					case eSampleRateKind::esrk44kHz: return sample_rate_trait<eSampleRateKind::esrk44kHz>::SAMPLE_PER_SECOND;
					case eSampleRateKind::esrk48kHz: return sample_rate_trait<eSampleRateKind::esrk48kHz>::SAMPLE_PER_SECOND;
					case eSampleRateKind::esrk96kHz: return sample_rate_trait<eSampleRateKind::esrk96kHz>::SAMPLE_PER_SECOND;
					case eSampleRateKind::esrk192kHz: return sample_rate_trait<eSampleRateKind::esrk192kHz>::SAMPLE_PER_SECOND;
				}
			}
		};

		enum eSampleFormatKind : uint8_t {
			esfkU8Bit, esfkS16Bit
		};

		template <eSampleFormatKind sfk>
		struct sample_format_trait { };

		template <>
		struct sample_format_trait<esfkU8Bit> {
			using type = std::uint8_t;
			static constexpr size_t SIZE = sizeof(type);
			static constexpr size_t BIT_SIZE = SIZE * 8;
			static constexpr bool IS_SIGNED = false;
			static const type MAX_VALUE = 255;

			template <eFloatingPointKind fpk>
			static type convFromFP(TFPKind<fpk> from) {
				return (from + 1.0) / 2.0 * MAX_VALUE;
			}
		};

		template <>
		struct sample_format_trait<esfkS16Bit> {
			using type = std::int16_t;
			static constexpr size_t SIZE = sizeof(type);
			static constexpr size_t BIT_SIZE = SIZE * 8;
			static constexpr bool IS_SIGNED = true;
			static const type MAX_VALUE = 32767;

			template <eFloatingPointKind fpk>
			static type convFromFP(TFPKind<fpk> from) {
				return type(from * MAX_VALUE);
			}

		};

		struct ISampleFormatKind
		{
			virtual eSampleFormatKind getSampleFormatKind() const noexcept = 0;
			size_t getSampleFormatSize() const noexcept
			{
				switch (this->getSampleFormatKind())
				{
					case esfkU8Bit: return sample_format_trait<esfkU8Bit>::SIZE;
						break;
					case esfkS16Bit: return sample_format_trait<esfkS16Bit>::SIZE;
						break;
				}
			}

			size_t getSampleFormatBitSize() const noexcept
			{
				switch (this->getSampleFormatKind())
				{
				case esfkU8Bit: return sample_format_trait<esfkU8Bit>::BIT_SIZE;
				case esfkS16Bit: return sample_format_trait<esfkS16Bit>::BIT_SIZE;
				}
			}

			size_t isSampleFormatSigned() const noexcept
			{
				switch (this->getSampleFormatKind())
				{
					case esfkU8Bit: return sample_format_trait<esfkU8Bit>::IS_SIGNED;
					case esfkS16Bit: return sample_format_trait<esfkS16Bit>::IS_SIGNED;
				}
			}

			size_t getSampleFormatMaxValue() const noexcept
			{
				switch (this->getSampleFormatKind())
				{
					case esfkU8Bit: return sample_format_trait<esfkU8Bit>::MAX_VALUE;
					case esfkS16Bit: return sample_format_trait<esfkS16Bit>::MAX_VALUE;
				}
			}
		};

		//
		// Channel Count
		//
		struct IChannelCount
		{
			virtual uint8_t getChannelCount() const noexcept = 0;
		};

		struct IAudioDevice :
			public ISampleFormatKind,
			public ISampleRateKind,
			public IChannelCount
		{
			virtual uint32_t getBufferSampleCapacity() const noexcept = 0;
		};

		template <typename T>
		struct IAudioDeviceOutputT :
			public IAudioDevice
		{
			virtual void lockBuffer(typename T** pBuff) noexcept = 0;
			virtual void unlockBuffer(typename T** pBuff, uint32_t sampleWritten) noexcept = 0;
		};


		template <eSampleFormatKind sfk>
		struct CWaveFileWriter :
			public IAudioDeviceOutputT<typename sample_format_trait<sfk>::type>
		{
			using type = typename sample_format_trait<sfk>::type;

			~CWaveFileWriter()
			{
				uint32_t RiffChunkSize = this->getRIFFChunkSize();

				//write size
				m_OFStream.seekp(4);
				m_OFStream.write((const char*)&RiffChunkSize, 4);
				m_OFStream.seekp(40);
				m_OFStream.write((const char*)&this->m_DataChunkSize, 4);
				m_OFStream.close();

				delete this->m_pBuffer;
				this->m_pBuffer = nullptr;
			}

			CWaveFileWriter() = delete;
			CWaveFileWriter(const CWaveFileWriter&) = delete;
			void operator = (const CWaveFileWriter&) = delete;
			CWaveFileWriter(CWaveFileWriter<sfk>&& rvalue) = delete;
			void operator = (CWaveFileWriter&&) = delete;


			CWaveFileWriter(std::string fname, eSampleRateKind srk, uint8_t nChannel,uint32_t buffSampleCapacity = 1024) :
				m_SampleRateKind(srk),
				m_ChannelCount(nChannel),
				m_BufferSampleCapacity(buffSampleCapacity),
				m_OFStream(fname, std::ios::binary | std::ios::out),
				m_DataChunkSize(0)
			{
				int32_t		tmp_i4;
				int16_t		tmp_i2;

				// allocate buffer memory
				this->m_pBuffer = (type*)std::malloc(this->getSampleFormatSize() * this->getChannelCount() * this->m_BufferSampleCapacity);

				// initialize file
				m_OFStream.write("RIFF", 4);
				tmp_i4 = 0;
				m_OFStream.write((const char*)&tmp_i4, 4); //  chunk size, write on destructor
				m_OFStream.write("WAVE", 4);
				m_OFStream.write("fmt ", 4);

				// Size of fmt chunk
				tmp_i4 = 16;
				m_OFStream.write((const char*)&tmp_i4, 4); // fmt size

				// Kind : PCM
				tmp_i2 = 1;
				m_OFStream.write((const char*)&tmp_i2, 2);

				// Num Channel
				tmp_i2 = this->getChannelCount();
				m_OFStream.write((const char*)&tmp_i2, 2);

				// Sample Rate
				tmp_i4 = this->getSampleRate();
				m_OFStream.write((const char*)&tmp_i4, 4);

				// Byte Rate
				tmp_i4 = this->getByteRate();
				m_OFStream.write((const char*)&tmp_i4, 4); // Byte Rate

				// Block Align (2)
				tmp_i2 = this->getBlockAlign();
				m_OFStream.write((const char*)&tmp_i2, 2);

				// Bits Per Sample (2)
				tmp_i2 = this->getBitsPerMonoSample();
				m_OFStream.write((const char*)&tmp_i2, 2);

				// "data" Chunk
				m_OFStream.write("data", 4);
				m_OFStream.write("1234", 4); // "data" chunk size, fille with dummy
			}

			std::string_view getFilename() const noexcept
			{
				return this->m_Filename;
			}

			eSampleFormatKind getSampleFormatKind() const noexcept final
			{
				return sfk;
			}

			eSampleRateKind getSampleRateKind() const noexcept final
			{
				return this->m_SampleRateKind;
			}

			uint8_t getChannelCount() const noexcept final
			{
				return this->m_ChannelCount;
			}

			uint32_t getRIFFChunkSize() const noexcept
			{
				return this->m_DataChunkSize + 36;
			}

			uint32_t getDataChunkSize() const noexcept
			{
				return this->m_DataChunkSize;
			}

			uint32_t getSampleSize() const noexcept
			{
				return this->getSampleFormatSize() * this->getChannelCount();
			}

			uint32_t getBufferSampleCapacity() const noexcept final
			{
				return this->m_BufferSampleCapacity;
			}

			void lockBuffer(typename sample_format_trait<sfk>::type **pBuff) noexcept final
			{
				*pBuff = this->m_pBuffer;
			}

			void unlockBuffer(typename sample_format_trait<sfk>::type** pBuff,uint32_t sampleWritten) noexcept final
			{
				*pBuff = nullptr;

				this->m_DataChunkSize += (sampleWritten * this->getSampleSize());

				m_OFStream.seekp(0, std::ios_base::end);
				m_OFStream.write(((const char*)this->m_pBuffer), (sampleWritten * this->getSampleSize()));
			}

		private:

			uint16_t getBitsPerMonoSample() const noexcept
			{
				return this->getSampleFormatBitSize();
			}

			uint32_t getByteRate() const noexcept
			{
				return (uint32_t)this->getSampleRate() *
					(uint32_t)this->getChannelCount() *
					(uint32_t)this->getSampleFormatSize();
			}

			uint16_t getBlockAlign() const noexcept
			{
				return this->getChannelCount() * this->getSampleFormatSize();
			}

			eSampleRateKind								m_SampleRateKind;
			uint8_t										m_ChannelCount;
			uint32_t									m_BufferSampleCapacity;
			typename sample_format_trait<sfk>::type*	m_pBuffer;

			uint32_t									m_DataChunkSize;
			std::ofstream								m_OFStream;
		};


	}
}