#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Oscillator
{

	TEST_CLASS(Noise)
	{
	public:

		TEST_METHOD(Basic)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscnoise-basic.wav", esrk48kHz, 1);

			COscNoise<FP_KIND> noise;
			CAudioConverter<SF_KIND, FP_KIND> genAudio(noise);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}
	};

}
