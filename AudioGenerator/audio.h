#pragma once

#include "eFloatingPointKind.h"
#include "CAbsOperator.h"
#include <cstdint>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>

namespace ipgdlib
{
	namespace audio
	{
		inline constexpr double freqMap[] = {
			16.35,17.32,18.35,19.45,20.6,21.83,23.12,24.5,25.96,27.5,29.14,30.87,
			32.7,34.65,36.71,38.89,41.2,43.65,46.25,49,51.91,55,58.27,61.74,
			65.41,69.3,73.42,77.78,82.41,87.31,92.5,98,103.83,110,116.54,123.47,
			130.81,138.59,146.83,155.56,164.81,174.61,185,196,207.65,220,233.08,246.94,
			261.63,277.18,293.66,311.13,329.63,349.23,369.99,392,415.3,440,466.16,493.88,
			523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880,932.33,987.77,
			1046.5,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760,1864.66,1975.53,
			2093,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520,3729.31,3951.07,
			4186.41,4434.92,4698.63,4978.03,5274.04,5587.65,5919.91,6271.93,6644.88,7040,7458.62,7902.13,
		};

		inline std::map<std::string, uint8_t> noteSharp2IdxFreqMap({
			{"C0", 0},{"C#0", 1},{"D0", 2},{"D#0", 3},{"E0",  4},{"F0",  5},{"F#0",  6},{"G0",  7},{"G#0",  8},{"A0",  9},{"A#0", 10},{"B0", 11},
			{"C1",12},{"C#1",13},{"D1",14},{"D#1",15},{"E1", 16},{"F1", 17},{"F#1", 18},{"G1", 19},{"G#1", 20},{"A1", 21},{"A#1", 22},{"B1", 23},
			{"C2",24},{"C#2",25},{"D2",26},{"D#2",27},{"E2", 28},{"F2", 29},{"F#2", 30},{"G2", 31},{"G#2", 32},{"A2", 33},{"A#2", 34},{"B2", 35},
			{"C3",36},{"C#3",37},{"D3",38},{"D#3",39},{"E3", 40},{"F3", 41},{"F#3", 42},{"G3", 43},{"G#3", 44},{"A3", 45},{"A#3", 46},{"B3", 47},
			{"C4",48},{"C#4",49},{"D4",50},{"D#4",51},{"E4", 52},{"F4", 53},{"F#4", 54},{"G4", 55},{"G#4", 56},{"A4", 57},{"A#4", 58},{"B4", 59},
			{"C5",60},{"C#5",61},{"D5",62},{"D#5",63},{"E5", 64},{"F5", 65},{"F#5", 66},{"G5", 67},{"G#5", 68},{"A5", 69},{"A#5", 70},{"B5", 71},
			{"C6",72},{"C#6",73},{"D6",74},{"D#6",75},{"E6", 76},{"F6", 77},{"F#6", 78},{"G6", 79},{"G#6", 80},{"A6", 81},{"A#6", 82},{"B6", 83},
			{"C7",84},{"C#7",85},{"D7",86},{"D#7",87},{"E7", 88},{"F7", 89},{"F#7", 90},{"G7", 91},{"G#7", 92},{"A7", 93},{"A#7", 94},{"B7", 95},
			{"C8",96},{"C#8",97},{"D8",98},{"D#8",99},{"E8",100},{"F8",101},{"F#8",102},{"G8",103},{"G#8",104},{"A8",105},{"A#8",106},{"B8",107}
		});

		inline std::map<std::string, uint8_t> noteFlat2IdxFreqMap({
			{"C0", 0},{"Db0", 1},{"D0", 2},{"Eb0", 3},{"E0",  4},{"F0",  5},{"Gb0",  6},{"G0",  7},{"Ab0",  8},{"A0",  9},{"Bb0", 10},{"B0", 11},
			{"C1",12},{"Db1",13},{"D1",14},{"Eb1",15},{"E1", 16},{"F1", 17},{"Gb1", 18},{"G1", 19},{"Ab1", 20},{"A1", 21},{"Bb1", 22},{"B1", 23},
			{"C2",24},{"Db2",25},{"D2",26},{"Eb2",27},{"E2", 28},{"F2", 29},{"Gb2", 30},{"G2", 31},{"Ab2", 32},{"A2", 33},{"Bb2", 34},{"B2", 35},
			{"C3",36},{"Db3",37},{"D3",38},{"Eb3",39},{"E3", 40},{"F3", 41},{"Gb3", 42},{"G3", 43},{"Ab3", 44},{"A3", 45},{"Bb3", 46},{"B3", 47},
			{"C4",48},{"Db4",49},{"D4",50},{"Eb4",51},{"E4", 52},{"F4", 53},{"Gb4", 54},{"G4", 55},{"Ab4", 56},{"A4", 57},{"Bb4", 58},{"B4", 59},
			{"C5",60},{"Db5",61},{"D5",62},{"Eb5",63},{"E5", 64},{"F5", 65},{"Gb5", 66},{"G5", 67},{"Ab5", 68},{"A5", 69},{"Bb5", 70},{"B5", 71},
			{"C6",72},{"Db6",73},{"D6",74},{"Eb6",75},{"E6", 76},{"F6", 77},{"Gb6", 78},{"G6", 79},{"Ab6", 80},{"A6", 81},{"Bb6", 82},{"B6", 83},
			{"C7",84},{"Db7",85},{"D7",86},{"Eb7",87},{"E7", 88},{"F7", 89},{"Gb7", 90},{"G7", 91},{"Ab7", 92},{"A7", 93},{"Bb7", 94},{"B7", 95},
			{"C8",96},{"Db8",97},{"D8",98},{"Eb8",99},{"E8",100},{"F8",101},{"Gb8",102},{"G8",103},{"Ab8",104},{"A8",105},{"Bb8",106},{"B8",107}
		});

		inline std::map<std::string, uint8_t> note2IdxFreqMap({
			{"C0", 0},{"C#0", 1},{"Db0", 1},{"D0", 2},{"D#0",  3},{"Eb0", 3},{"E0",  4},{"F0",  5},{"F#0",  6},{"Gb0",  6},{"G0",  7},{"G#0",  8},{"Ab0",  8},{"A0",  9},{"A#0", 10},{"Bb0", 10},{"B0", 11},
			{"C1",12},{"C#1",13},{"Db1",13},{"D1",14},{"D#1", 15},{"Eb1",15},{"E1", 16},{"F1", 17},{"F#1", 18},{"Gb1", 18},{"G1", 19},{"G#1", 20},{"Ab1", 20},{"A1", 21},{"A#1", 22},{"Bb1", 22},{"B1", 23},
			{"C2",24},{"C#2",25},{"Db2",25},{"D2",26},{"D#2", 27},{"Eb2",27},{"E2", 28},{"F2", 29},{"F#2", 30},{"Gb2", 30},{"G2", 31},{"G#2", 32},{"Ab2", 32},{"A2", 33},{"A#2", 34},{"Bb2", 34},{"B2", 35},
			{"C3",36},{"C#3",37},{"Db3",37},{"D3",38},{"D#3", 39},{"Eb3",39},{"E3", 40},{"F3", 41},{"F#3", 42},{"Gb3", 42},{"G3", 43},{"G#3", 44},{"Ab3", 44},{"A3", 45},{"A#3", 46},{"Bb3", 46},{"B3", 47},
			{"C4",48},{"C#4",49},{"Db4",49},{"D4",50},{"D#4", 51},{"Eb4",51},{"E4", 52},{"F4", 53},{"F#4", 54},{"Gb4", 54},{"G4", 55},{"G#4", 56},{"Ab4", 56},{"A4", 57},{"A#4", 58},{"Bb4", 58},{"B4", 59},
			{"C5",60},{"C#5",61},{"Db5",61},{"D5",62},{"D#5", 63},{"Eb5",63},{"E5", 64},{"F5", 65},{"F#5", 66},{"Gb5", 66},{"G5", 67},{"G#5", 68},{"Ab5", 68},{"A5", 69},{"A#5", 70},{"Bb5", 70},{"B5", 71},
			{"C6",72},{"C#6",73},{"Db6",73},{"D6",74},{"D#6", 75},{"Eb6",75},{"E6", 76},{"F6", 77},{"F#6", 78},{"Gb6", 78},{"G6", 79},{"G#6", 80},{"Ab6", 80},{"A6", 81},{"A#6", 82},{"Bb6", 82},{"B6", 83},
			{"C7",84},{"C#7",85},{"Db7",85},{"D7",86},{"D#7", 87},{"Eb7",87},{"E7", 88},{"F7", 89},{"F#7", 90},{"Gb7", 90},{"G7", 91},{"G#7", 92},{"Ab7", 92},{"A7", 93},{"A#7", 94},{"Bb7", 94},{"B7", 95},
			{"C8",96},{"C#8",97},{"Db8",97},{"D8",98},{"D#8", 99},{"Eb8",99},{"E8",100},{"F8",101},{"F#8",102},{"Gb8",102},{"G8",103},{"G#8",104},{"Ab8",104},{"A8",105},{"A#8",106},{"Bb8",106},{"B8",107}
		});


		inline std::map<uint8_t,const char*> idxFreq2SharpNoteMap({
			{ 0,"C0"},{ 1,"C#0"},{ 2,"D0"},{ 3,"D#0"},{  4,"E0"},{  5,"F0"},{  6,"F#0"},{  7,"G0"},{  8,"G#0"},{  9,"A0"},{ 10,"A#0"},{ 11,"B0"},
			{12,"C1"},{13,"C#1"},{14,"D1"},{15,"D#1"},{ 16,"E1"},{ 17,"F1"},{ 18,"F#1"},{ 19,"G1"},{ 20,"G#1"},{ 21,"A1"},{ 22,"A#1"},{ 23,"B1"},
			{24,"C2"},{25,"C#2"},{26,"D2"},{27,"D#2"},{ 28,"E2"},{ 29,"F2"},{ 30,"F#2"},{ 31,"G2"},{ 32,"G#2"},{ 33,"A2"},{ 34,"A#2"},{ 35,"B2"},
			{36,"C3"},{37,"C#3"},{38,"D3"},{39,"D#3"},{ 40,"E3"},{ 41,"F3"},{ 42,"F#3"},{ 43,"G3"},{ 44,"G#3"},{ 45,"A3"},{ 46,"A#3"},{ 47,"B3"},
			{48,"C4"},{49,"C#4"},{50,"D4"},{51,"D#4"},{ 52,"E4"},{ 53,"F4"},{ 54,"F#4"},{ 55,"G4"},{ 56,"G#4"},{ 57,"A4"},{ 58,"A#4"},{ 59,"B4"},
			{60,"C5"},{61,"C#5"},{62,"D5"},{63,"D#5"},{ 64,"E5"},{ 65,"F5"},{ 66,"F#5"},{ 67,"G5"},{ 68,"G#5"},{ 69,"A5"},{ 70,"A#5"},{ 71,"B5"},
			{72,"C6"},{73,"C#6"},{74,"D6"},{75,"D#6"},{ 76,"E6"},{ 77,"F6"},{ 78,"F#6"},{ 79,"G6"},{ 80,"G#6"},{ 81,"A6"},{ 82,"A#6"},{ 83,"B6"},
			{84,"C7"},{85,"C#7"},{86,"D7"},{87,"D#7"},{ 88,"E7"},{ 89,"F7"},{ 90,"F#7"},{ 91,"G7"},{ 92,"G#7"},{ 93,"A7"},{ 94,"A#7"},{ 95,"B7"},
			{96,"C8"},{97,"C#8"},{98,"D8"},{99,"D#8"},{100,"E8"},{101,"F8"},{102,"F#8"},{103,"G8"},{104,"G#8"},{105,"A8"},{106,"A#8"},{107,"B8"}
		});

		inline std::map<uint8_t, const char*> idxFreq2FlatNoteMap({
			{ 0,"C0"},{ 1,"Db0"},{ 2,"D0"},{ 3,"Eb0"},{  4,"E0"},{  5,"F0"},{  6,"Gb0"},{  7,"G0"},{  8,"Ab0"},{  9,"A0"},{ 10,"Bb0"},{ 11,"B0"},
			{12,"C1"},{13,"Db1"},{14,"D1"},{15,"Eb1"},{ 16,"E1"},{ 17,"F1"},{ 18,"Gb1"},{ 19,"G1"},{ 20,"Ab1"},{ 21,"A1"},{ 22,"Bb1"},{ 23,"B1"},
			{24,"C2"},{25,"Db2"},{26,"D2"},{27,"Eb2"},{ 28,"E2"},{ 29,"F2"},{ 30,"Gb2"},{ 31,"G2"},{ 32,"Ab2"},{ 33,"A2"},{ 34,"Bb2"},{ 35,"B2"},
			{36,"C3"},{37,"Db3"},{38,"D3"},{39,"Eb3"},{ 40,"E3"},{ 41,"F3"},{ 42,"Gb3"},{ 43,"G3"},{ 44,"Ab3"},{ 45,"A3"},{ 46,"Bb3"},{ 47,"B3"},
			{48,"C4"},{49,"Db4"},{50,"D4"},{51,"Eb4"},{ 52,"E4"},{ 53,"F4"},{ 54,"Gb4"},{ 55,"G4"},{ 56,"Ab4"},{ 57,"A4"},{ 58,"Bb4"},{ 59,"B4"},
			{60,"C5"},{61,"Db5"},{62,"D5"},{63,"Eb5"},{ 64,"E5"},{ 65,"F5"},{ 66,"Gb5"},{ 67,"G5"},{ 68,"Ab5"},{ 69,"A5"},{ 70,"Bb5"},{ 71,"B5"},
			{72,"C6"},{73,"Db6"},{74,"D6"},{75,"Eb6"},{ 76,"E6"},{ 77,"F6"},{ 78,"Gb6"},{ 79,"G6"},{ 80,"Ab6"},{ 81,"A6"},{ 82,"Bb6"},{ 83,"B6"},
			{84,"C7"},{85,"Db7"},{86,"D7"},{87,"Eb7"},{ 88,"E7"},{ 89,"F7"},{ 90,"Gb7"},{ 91,"G7"},{ 92,"Ab7"},{ 93,"A7"},{ 94,"Bb7"},{ 95,"B7"},
			{96,"C8"},{97,"Db8"},{98,"D8"},{99,"Eb8"},{100,"E8"},{101,"F8"},{102,"Gb8"},{103,"G8"},{104,"Ab8"},{105,"A8"},{106,"Bb8"},{107,"B8"}
		});
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

		struct beat_t
		{
			beat_t() :
				beat_t(0)
			{
			}

			beat_t(uint8_t m) :
				mul(m), div(1)
			{
			}

			beat_t(uint8_t m, uint8_t d) :
				mul(m), div(d)
			{
				if (d == 0)
					throw std::invalid_argument("divisor cannot be 0");
			}

			uint8_t mul;
			uint8_t div;

		};

		inline std::ostream& operator << (std::ostream& os, beat_t beat)
		{
			if (beat.mul == 0)
			{
				os << (int)0;
			}
			else
				if (beat.div == 1)
					os << (int)beat.mul;
				else
					os << (int)beat.mul << '/' << (int)beat.div;
			return os;
		}

		inline std::istream& operator >> (std::istream& is, beat_t & beat)
		{
			int val;

			is >> val;
			beat.mul = val;
			if (val == 0)
				beat.div = 1;
			else
			{
				if (is.peek() == '/')
				{
					is.get();
					is >> val;
					beat.div = val;
				}
				else
					beat.div = 1;
			}

			return is;
		}

		struct CNoteLane
		{

			struct note_t
			{
				note_t() :
					note(0),length(),prev(),duration(0.98)
				{
				}

				note_t(uint8_t _note, beat_t _noteBeat) :
					note_t(_note, _noteBeat, 0.98, {})
				{
				}

				note_t(uint8_t _note, beat_t _noteBeat,beat_t _prev) :
					note_t(_note, _noteBeat, 0.98, _prev)
				{
				}

				note_t(uint8_t _note, beat_t _noteBeat,float _duration,beat_t _prev) :
					note(_note), length(_noteBeat), duration(_duration),prev(_prev)
				{
				}

				uint8_t note;
				const char* getNoteName(bool bFlat = false)
				{
					if (bFlat)
						return idxFreq2FlatNoteMap[note];
					else
						return idxFreq2SharpNoteMap[note];
				}

				bool isRestZero() const noexcept
				{
					return this->prev.mul == 0;
				}

				beat_t length;
				float duration;
				beat_t prev;
			};

			CNoteLane() :
				m_Notes()
			{
			}

			CNoteLane(const char * filename)
			{
				this->loadFromFile(filename);
			}

			CNoteLane(std::vector<note_t> notes) :
				m_Notes(std::move(notes))
			{
			}

			size_t getNoteCount() const noexcept
			{
				return this->m_Notes.size();
			}

			note_t getNote(size_t index) const
			{
				return this->m_Notes[index];
			}

			void setNote(size_t index, note_t note)
			{
				this->m_Notes[index] = note;
			}

			void appendNote(note_t note)
			{
				this->m_Notes.push_back(note);
			}
			void appendNotes(std::vector<note_t> notes)
			{
				this->m_Notes.insert(this->m_Notes.cend(),notes.begin(),notes.end());
			}

			void setNotes(std::vector<note_t> notes)
			{
				this->m_Notes = std::move(notes);
			}

			void loadFromFile(const char* filename)
			{
				note_t note;
				std::string tmp;

				std::ifstream fin;
				fin.open(filename);

				if (fin.is_open())
				{
					m_Notes.clear();
					do
					{
						fin >> tmp;
						if (fin.eof())
							break;
						if (tmp.find('b') == std::string::npos)
							note.note = noteSharp2IdxFreqMap[tmp];
						else
							note.note = noteFlat2IdxFreqMap[tmp];
						fin >> note.length;
						fin >> note.prev;
						m_Notes.push_back(note);
					} while (true);
				}
				fin.close();
			}

			void saveToFile(const char* filename,bool bFlat = false)
			{
				std::ofstream fout(filename);

				if (fout.is_open())
				{
					for (auto i : m_Notes)
						fout << i.getNoteName(bFlat) << '\t' << i.length << '\t' << i.prev << std::endl;
				}
			}

		private:
			std::vector<note_t>     m_Notes;

		};


	}
}