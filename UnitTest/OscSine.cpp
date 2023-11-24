#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Oscillator
{
	TEST_CLASS(Sine)
	{

	public:
		TEST_METHOD(Basic)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscsine-basic.wav", esrk48kHz, 1);

			COscSine<FLOATING_POINT_KIND> sigSine(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0))
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}

		TEST_METHOD(AMSine)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscsine-amsine.wav", esrk48kHz, 1);

			COscSine<FLOATING_POINT_KIND> sigSine(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0))
			);

			COCBMul<FLOATING_POINT_TYPE> AM(
				sigSine,
				new COCUCustom<FLOATING_POINT_TYPE>(
					[](FLOATING_POINT_TYPE x) {
						return 0.8 + x/5.0;
					},
					new COscSine<FLOATING_POINT_KIND>(
						new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(8.0))
					)
				)
			);

			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(AM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 5000);

			delete pFileOut;
		}

		TEST_METHOD(AMSelector)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscsine-amselector.wav", esrk48kHz, 1);

			COscSine<FLOATING_POINT_KIND> sigSine(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0))
			);

			COCBMul<FLOATING_POINT_TYPE> AM(
				sigSine,
				new CGenFiniteConstant<FLOATING_POINT_TYPE>(
					{
						{10000,0.0},
						{10000,0.2},
						{10000,0.4},
						{10000,0.6},
						{10000,0.8},
						{10000,1.0}
					}
				)
			);

			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(AM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 5000);

			delete pFileOut;
		}

		TEST_METHOD(AMEnvelope)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscsine-amenvelope.wav", esrk48kHz, 1);

			COscSine<FLOATING_POINT_KIND> sigSine(
				new COscFreq<FLOATING_POINT_KIND>(SAMPLE_RATE, new CGenConstant<FLOATING_POINT_TYPE>(440.0))
			);

			COCBMul<FLOATING_POINT_TYPE> AM(
				sigSine,
				new CEnvelope<FLOATING_POINT_KIND>(
					{10000,10000,0.8,10000},
					new CGenFiniteConstant<eGateKind>({
						{30000,egkOn},
						{15000,egkOff},
						{30000,egkOn},
						{15000,egkOff},
					})
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(AM);
			
			// agregate 2 sound
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);

			//change linear to power
			dynamic_cast<CEnvelope<FLOATING_POINT_KIND>&>(AM.getRightOperand()).setFunctions({
				function::fnPower<FLOATING_POINT_KIND>(2.0),
				function::fnPower<FLOATING_POINT_KIND>(2.0),
				function::fnPower<FLOATING_POINT_KIND>(2.0),
			});
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);
			
			// change back to linear
			dynamic_cast<CEnvelope<FLOATING_POINT_KIND>&>(AM.getRightOperand()).setFunctions({
				function::fnLinear<FLOATING_POINT_TYPE>,
				function::fnLinear<FLOATING_POINT_TYPE>,
				function::fnLinear<FLOATING_POINT_TYPE>,
			});
			dynamic_cast<CEnvelope<FLOATING_POINT_KIND>&>(AM.getRightOperand()).setADSR(
				{ 10000,20000,0,0 }
			);
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);

			dynamic_cast<CEnvelope<FLOATING_POINT_KIND>&>(AM.getRightOperand()).setFunctions({
				function::fnPower<FLOATING_POINT_KIND>(2.0),
				function::fnPower<FLOATING_POINT_KIND>(2.0),
				function::fnPower<FLOATING_POINT_KIND>(2.0),
			});
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);

			delete pFileOut;
		}

		TEST_METHOD(FMLinearUp)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscsine-fmlinearup.wav", esrk48kHz, 1);

			COscSine<FLOATING_POINT_KIND> sigSine(
				new COscFreq<FLOATING_POINT_KIND>(
					SAMPLE_RATE,
					new COCUCustom<FLOATING_POINT_TYPE>(
						[](FLOATING_POINT_TYPE x) {
							return 440 + 200 * x;
						},
						new COscFreq<FLOATING_POINT_KIND>(
							SAMPLE_RATE,
							new CGenConstant<FLOATING_POINT_TYPE>(2.0)
						)
					)
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}
		TEST_METHOD(FMLinearDown)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscsine-fmlineardown.wav", esrk48kHz, 1);

			COscSine<FLOATING_POINT_KIND> sigSine(
				new COscFreq<FLOATING_POINT_KIND>(
					SAMPLE_RATE,
					new COCUCustom<FLOATING_POINT_TYPE>(
						[](FLOATING_POINT_TYPE x) {
							return 640 - 200 * x;
						},
						new COscFreq<FLOATING_POINT_KIND>(
							SAMPLE_RATE,
							new CGenConstant<FLOATING_POINT_TYPE>(2.0)
						)
					)
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(FMSine)
		{
			auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("oscsine-fmsine.wav", esrk48kHz, 1);

			COscSine<FLOATING_POINT_KIND> sigSine(
				new COscFreq<FLOATING_POINT_KIND>(
					SAMPLE_RATE,
					new COCUCustom<FLOATING_POINT_TYPE>(
						[](FLOATING_POINT_TYPE x) {
							return 440 - 20 * x;
						},
						new COscSine<FLOATING_POINT_KIND>(
							new COscFreq<FLOATING_POINT_KIND>(
								SAMPLE_RATE,
								new CGenConstant<FLOATING_POINT_TYPE>(16.0)
							)
						)
					)
				)
			);
			CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}
	};

}
