#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Oscillator
{
	TEST_CLASS(Power)
	{
	public:
		TEST_METHOD(Basic)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpower-basic.wav", esrk48kHz, 1);

			COscPower<FP_KIND> sigPower(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new CGenConstant<FP_TYPE>(2)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPower);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}

		TEST_METHOD(SweepUp)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpower-sweepup.wav", esrk48kHz, 1);

			COscPower<FP_KIND> sigPower(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPower);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepDown)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpower-sweepdown.wav", esrk48kHz, 1);

			COscPower<FP_KIND> sigPower(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COCUInvert<FP_KIND>(
					new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPower);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepSine)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpower-sweepsine.wav", esrk48kHz, 1);

			COscPower<FP_KIND> sigPower(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COscNormalize<FP_KIND>(
					new COscSine<FP_KIND>(
						new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
					)
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPower);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}
	};
}
