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
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscexponent-basic.wav", esrk48kHz, 1);

			COscExponent<FLOATING_POINT_KIND> sigExponent(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new CGenConstant<FLOATING_POINT_TYPE>(2)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}

		TEST_METHOD(SweepUp)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscexponent-sweepup.wav", esrk48kHz, 1);

			COscExponent<FLOATING_POINT_KIND> sigExponent(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(0.1))
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepDown)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscexponent-sweepdown.wav", esrk48kHz, 1);

			COscExponent<FLOATING_POINT_KIND> sigExponent(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new COCUInvert<FLOATING_POINT_KIND>(
					new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(0.1))
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepSine)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscexponent-sweepsine.wav", esrk48kHz, 1);

			COscExponent<FLOATING_POINT_KIND> sigExponent(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new COscNormalize<FLOATING_POINT_KIND>(
					new COscSine<FLOATING_POINT_KIND>(
						new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(0.1))
					)
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigExponent);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}
	};
}
