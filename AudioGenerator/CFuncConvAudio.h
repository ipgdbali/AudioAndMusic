#pragma once

#include "CAbsOperatorT.h"
#include "IOperatorT.h"
#include "eFloatingPointKind.h"
#include "audio.h"

using namespace ipgdlib::op;

namespace ipgdlib
{
	namespace audio
	{

		template <eSampleFormatKind sfk,eFloatingPointKind fpk>
		struct CFuncConvAudio :
			public CAbsOperatorT<typename sample_format_trait<sfk>::type>
		{

			using float_type = TFPKind<fpk>;
			using ret_type = typename sample_format_trait<sfk>::type;
			using param_type = pointer_deleter<IOperatorT<TFPKind<fpk>>>;
			
			CFuncConvAudio(param_type source) :
				CAbsOperatorT<ret_type>({source.as<IOperator>()})
			{
			}

			ret_type get() noexcept final
			{
				return sample_format_trait<sfk>::convFromFP<fpk>(this->m_Source->get());
			}

		private:
			IOperatorT<TFPKind<fpk>> *m_Source;

		};

		template <typename T>
		void audioAgregateMillis(
			pointer_deleter<IAudioDeviceOutputT<T>> audioOut,
			pointer_deleter<IOperatorT<T>> signal,
			size_t millis
		)
		{
			T* pBuffer;

			size_t target = audioOut->getSampleRate() / 1000 * millis;
			while (target > 0)
			{
				audioOut->lockBuffer(&pBuffer);
				size_t writtenSample =
					(target > audioOut->getBufferSampleCapacity()) ? audioOut->getBufferSampleCapacity() : target;

				for (size_t li = 0; li < writtenSample; li++)
					for (size_t lj = 0; lj < audioOut->getChannelCount(); lj++)
						pBuffer[li * audioOut->getChannelCount() + lj] = signal->get();

				audioOut->unlockBuffer(&pBuffer, writtenSample);
				target -= writtenSample;
			}
		}


	}
}


