#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Oscillator
{
	TEST_CLASS(Exponent)
	{
	public:
		TEST_METHOD(Basic)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscexponent-basic.wav", esrk48kHz, 1);

			COscExponent<FP_KIND> sigExponent(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new CGenConstant<FP_TYPE>(2)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}

		TEST_METHOD(SweepUp)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscexponent-sweepup.wav", esrk48kHz, 1);

			COscExponent<FP_KIND> sigExponent(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepDown)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscexponent-sweepdown.wav", esrk48kHz, 1);

			COscExponent<FP_KIND> sigExponent(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COCUInvert<FP_KIND>(
					new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepSine)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscexponent-sweepsine.wav", esrk48kHz, 1);

			COscExponent<FP_KIND> sigExponent(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COscNormalize<FP_KIND>(
					new COscSine<FP_KIND>(
						new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
					)
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}
	};
}
