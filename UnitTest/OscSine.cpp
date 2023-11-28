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
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-basic.wav", esrk48kHz, 1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0))
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 1000);

			delete pFileOut;
		}

		TEST_METHOD(AMSine)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-amsine.wav", esrk48kHz, 1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0))
			);

			COCBMul<FP_TYPE> AM(
				sigSine,
				new COCUCustom<FP_TYPE>(
					[](FP_TYPE x) {
						return 0.8 + x/5.0;
					},
					new COscSine<FP_KIND>(
						new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(8.0))
					)
				)
			);

			CAudioConverter<SF_KIND, FP_KIND> genAudio(AM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 5000);

			delete pFileOut;
		}

		TEST_METHOD(AMSelector)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-amselector.wav", esrk48kHz, 1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0))
			);

			COCBMul<FP_TYPE> AM(
				sigSine,
				new CGenFiniteConstant<FP_TYPE>(
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

			CAudioConverter<SF_KIND, FP_KIND> genAudio(AM);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 5000);

			delete pFileOut;
		}

		TEST_METHOD(AMEnvelope)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-amenvelope.wav", esrk48kHz, 1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(SAMPLE_RATE, new CGenConstant<FP_TYPE>(440.0))
			);

			COCBMul<FP_TYPE> AM(
				sigSine,
				new CEnvelopeADSR<FP_KIND>(
					{10000,10000,0.8,10000},
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

		TEST_METHOD(FMLinearUp)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-fmlinearup.wav", esrk48kHz, 1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(
					SAMPLE_RATE,
					new COCUOffsetScale<FP_KIND>(
						440.0,200.0,ipgdlib::function::fnLinear<FP_TYPE>,
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							new CGenConstant<FP_TYPE>(2.0)
						)
					)
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 5000);

			delete pFileOut;
		}
		TEST_METHOD(FMLinearDown)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-fmlineardown.wav", esrk48kHz, 1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(
					SAMPLE_RATE,
					new COCUOffsetScale<FP_KIND>(
						640.0, -200.0,
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							new CGenConstant<FP_TYPE>(2.0)
						)
					)
				)
			);
			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 5000);

			delete pFileOut;
		}

		TEST_METHOD(FMSine)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-fmsine.wav", esrk48kHz, 1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(
					SAMPLE_RATE,
					new COCUOffsetScale<FP_KIND>(
						440.0, 20.0,ipgdlib::function::fnLinear<FP_TYPE>,
						new COscSine<FP_KIND>(
							new COscFreq<FP_KIND>(
								SAMPLE_RATE,
								new CGenConstant<FP_TYPE>(2)
							)
						)
					)
				)
			);

			CAudioConverter<SF_KIND, FP_KIND> genAudio(sigSine);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 10000);

			delete pFileOut;
		}

		TEST_METHOD(NotesSingleTrack)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-notes-single-track.wav", esrk48kHz, 1);
			
			CNoteLane track1({
				{note2IdxFreqMap["E5"],{1,4}},
				{note2IdxFreqMap["D#5"],{1,4}},
				{note2IdxFreqMap["E5"],{1,4}},
				{note2IdxFreqMap["D#5"],{1,4}},
				{note2IdxFreqMap["E5"],{1,4}},
				{note2IdxFreqMap["B4"],{1,4}},
				{note2IdxFreqMap["D5"],{1,4}},
				{note2IdxFreqMap["C5"],{1,4}},
				{note2IdxFreqMap["A4"],{1,2}},
				
				{note2IdxFreqMap["E4"],{1,4},{1,4}},
				{note2IdxFreqMap["G#4"],{1,4}},
				{note2IdxFreqMap["A4"],{1,4}},
				{note2IdxFreqMap["B4"],{1,2}},

				{note2IdxFreqMap["G#4"],{1,4},{1,4}},
				{note2IdxFreqMap["A4"],{1,4}},
				{note2IdxFreqMap["B4"],{1,4}},
				{note2IdxFreqMap["C5"],{1,2}},

				{note2IdxFreqMap["E5"],{1,4},{1,2}},
				{note2IdxFreqMap["D#5"],{1,4}},
				{note2IdxFreqMap["E5"],{1,4}},
				{note2IdxFreqMap["D#5"],{1,4}},
				{note2IdxFreqMap["E5"],{1,4}},
				{note2IdxFreqMap["B4"],{1,4}},
				{note2IdxFreqMap["D5"],{1,4}},
				{note2IdxFreqMap["C5"],{1,4}},
				{note2IdxFreqMap["A4"],{1,2}},

				{note2IdxFreqMap["E4"],{1,4},{1,4}},
				{note2IdxFreqMap["G#4"],{1,4}},
				{note2IdxFreqMap["A4"],{1,4}},
				{note2IdxFreqMap["B4"],{1,2}},

				{note2IdxFreqMap["B4"],{1,4},{1,4}},
				{note2IdxFreqMap["C5"],{1,4}},
				{note2IdxFreqMap["B4"],{1,4}},
				{note2IdxFreqMap["A4"],{1,2}},

			});

			track1.saveToFile("track1.notes");

			CGenNotes<FP_KIND> gNotes(SAMPLE_RATE, 60, track1);

			COscSine<FP_KIND> sigSine(
				new COscFreq<FP_KIND>(
					SAMPLE_RATE,
					gNotes.getOpNoteFreq()
				)
			);

			CAudioConverter<SF_KIND, FP_KIND> genAudio(
				new COCBMul<FP_TYPE>(sigSine, new CEnvelopeADSR<FP_KIND>({100,0,0.8,100},gNotes.getOpNoteGate()))
			);
			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 12000);

			delete pFileOut;
		}

		TEST_METHOD(NotesMultiTrack)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("oscsine-notes-multi-track.wav", esrk48kHz, 1);

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
					new COscSine<FP_KIND>(
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							gTrack2.getOpNoteFreq()
						)
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
		}
	};

}
