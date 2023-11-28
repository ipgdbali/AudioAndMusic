#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Oscillator
{
	TEST_CLASS(PWM)
	{
	public:
		TEST_METHOD(Basic)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpwm-basic.wav", esrk48kHz, 1);

			COscPWM<FP_KIND> sigPWM(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new CGenConstant<FP_TYPE>(0.5)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPWM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}

		TEST_METHOD(SweepUp)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpwm-sweepup.wav", esrk48kHz, 1);

			COscPWM<FP_KIND> sigPWM(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPWM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepDown)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpwm-sweepdown.wav", esrk48kHz, 1);

			COscPWM<FP_KIND> sigPWM(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COCUInvert<FP_KIND>(
					new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPWM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(SweepSine)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpwm-sweepsine.wav", esrk48kHz, 1);

			COscPWM<FP_KIND> sigPWM(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new COscNormalize<FP_KIND>(
					new COscSine<FP_KIND>(
						new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(0.1))
					)
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigPWM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(AMEnvelope)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpwm-amenvelope.wav", esrk48kHz, 1);

			COscPWM<FP_KIND> sigPWM(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0)),
				new CGenConstant<FP_TYPE>(0.5)
			);

			COCBMul<FP_TYPE> AM(
				sigPWM,
				new CEnvelopeADSR<FP_KIND>(
					{ 10000,10000,0.8,10000 },
					new CGenFiniteConstant<eGateKind>({
						{30000,egkOn},
						{15000,egkOff},
						{30000,egkOn},
						{15000,egkOff},
					})
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(AM);

			// agregate 2 sound
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);

			//change linear to power
			dynamic_cast<CEnvelopeADSR<FP_KIND>&>(AM.getRightOperand()).setFunctions({
				function::fnPower<FP_KIND>(2.0),
				function::fnPower<FP_KIND>(2.0),
				function::fnPower<FP_KIND>(2.0),
				});
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);

			// change back to linear
			dynamic_cast<CEnvelopeADSR<FP_KIND>&>(AM.getRightOperand()).setFunctions({
				function::fnLinear<FP_TYPE>,
				function::fnLinear<FP_TYPE>,
				function::fnLinear<FP_TYPE>,
				});
			dynamic_cast<CEnvelopeADSR<FP_KIND>&>(AM.getRightOperand()).setADSR(
				{ 10000,20000,0,0 }
			);
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);

			dynamic_cast<CEnvelopeADSR<FP_KIND>&>(AM.getRightOperand()).setFunctions({
				function::fnPower<FP_KIND>(2.0),
				function::fnPower<FP_KIND>(2.0),
				function::fnPower<FP_KIND>(2.0),
				});
			audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 90000);

			delete pFileOut;
		}

		TEST_METHOD(NotesMultiTrack)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscpwm-notes-multi-track.wav", esrk48kHz, 1);

			CNoteLane track1("test.track1");
			CNoteLane track2("test.track2");

			CGenNotes<FP_KIND> gTrack1(SAMPLE_RATE, 60, track1);
			auto pInstr1 =
				new COCBMul<FP_TYPE>(
					new COscPWM<FP_KIND>(
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							gTrack1.getOpNoteFreq()
						),
						new CGenConstant<FP_TYPE>(0.5)
					),
					new CEnvelopeADSR<FP_KIND>({ 100,0,0.8,100 }, gTrack1.getOpNoteGate())
				);

			CGenNotes<FP_KIND> gTrack2(SAMPLE_RATE, 60, track2);
			auto pInstr2 =
				new COCBMul<FP_TYPE>(
					new COscPWM<FP_KIND>(
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							gTrack2.getOpNoteFreq()
						),
						new CGenConstant<FP_TYPE>(0.5)
					),
					new CEnvelopeADSR<FP_KIND>({ 100,0,0.8,100 }, gTrack2.getOpNoteGate())
				);

			CAudioConverter<SF_KIND, FP_KIND> genAudio(
				new COCMAdd<FP_TYPE>({
					new COCUMul<FP_TYPE>(
						0.5,
						pInstr1
					),
					new COCUMul<FP_TYPE>(
						0.5,
						pInstr2
					)
				})
			);

			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 4000);

			delete pFileOut;
		};

	};
}
