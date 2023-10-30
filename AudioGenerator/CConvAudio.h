#pragma once

#include "CAbsStreamProducerT.h"
#include "eFloatingPointKind.h"
#include "wrap_param.h"
#include "audio.h"

using namespace ipgdlib::stream;

namespace ipgdlib
{
	namespace audio
	{
		template <eSampleFormatKind sfk,eFloatingPointKind fpk, eWrapParam wp = ewpPointer>
		struct CConvAudio :
			public CAbsStreamProducerT<typename sample_format_trait<sfk>::type>
		{

			using float_type = TFPKind<fpk>;
			using ret_type = typename sample_format_trait<sfk>::type;
			using param_type = typename wrap_param<IStreamProducerT<float_type>, wp>;
			
			~CConvAudio()
			{
				if constexpr (wp == ewpPointer)
					this->m_Source.execute();
			}

			CConvAudio(typename param_type::type source) :
				m_Source(source)
			{
			}

			void reset() noexcept final
			{
				param_type::dereference(this->m_Source).reset();
			}

			ret_type get() noexcept final
			{
				return sample_format_trait<sfk>::convFromFP<fpk>(param_type::dereference(this->m_Source).get());
			}

		private:
			param_type::type m_Source;

		};

		template <typename T, eWrapParam wp = ewpPointer>
		void audioAgregateMillis(
			typename wrap_param<IAudioDeviceOutputT<T>, wp>::type audioOut,
			typename wrap_param<CAbsStreamProducerT<T>, wp>::type signal,
			size_t millis
		)
		{
			using out_param = wrap_param<IAudioDeviceOutputT<T>, wp>;
			using in_param = wrap_param<CAbsStreamProducerT<T>, wp>;

			T* pBuffer;

			size_t target = out_param::dereference(audioOut).getSampleRate() / 1000 * millis;
			while (target > 0)
			{
				out_param::dereference(audioOut).lockBuffer(&pBuffer);
				size_t writtenSample =
					(target > out_param::dereference(audioOut).getBufferSampleCapacity()) ? out_param::dereference(audioOut).getBufferSampleCapacity() : target;

				for (size_t li = 0; li < writtenSample; li++)
					for (size_t lj = 0; lj < out_param::dereference(audioOut).getChannelCount(); lj++)
						pBuffer[li * out_param::dereference(audioOut).getChannelCount() + lj] = in_param::dereference(signal).get();

				out_param::dereference(audioOut).unlockBuffer(&pBuffer, writtenSample);
				target -= writtenSample;
			}
		}


	}
}


