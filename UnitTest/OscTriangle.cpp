#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Oscillator
{
	TEST_CLASS(Triangle)
	{
	public:
		TEST_METHOD(Basic)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("osctriangle-basic.wav", esrk48kHz, 1);
			
			COscTriangle<FLOATING_POINT_KIND> sigTriangle(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE,new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new CGenConstant<FLOATING_POINT_TYPE>(0.5)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigTriangle);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}

		TEST_METHOD(SweepUp)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("osctriangle-sweepup.wav", esrk48kHz, 1);

			COscTriangle<FLOATING_POINT_KIND> sigTriangle(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(0.1))
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigTriangle);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepDown)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("osctriangle-sweepdown.wav", esrk48kHz, 1);

			COscTriangle<FLOATING_POINT_KIND> sigTriangle(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new COCUInvert<FLOATING_POINT_KIND>(
					new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(0.1))
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigTriangle);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepSine)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("osctriangle-sweepsine.wav", esrk48kHz, 1);

			COscTriangle<FLOATING_POINT_KIND> sigTriangle(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0)),
				new COscNormalize<FLOATING_POINT_KIND>(
					new COscSine<FLOATING_POINT_KIND>(
						new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(0.1))
					)
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigTriangle);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}
	};
}
