#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MusicPlayer
{
	TEST_CLASS(NES)
	{
	public:

		TEST_METHOD(Mario)
		{
			auto pFileOut = new CWaveFileWriter<SF_KIND>("musicplayer-nesmario.wav", esrk48kHz, 1);

			CNoteLane track1("mario.1.track");
			CNoteLane track2("mario.2.track");
			CNoteLane track3("mario.3.track");

			CGenNotes<FP_KIND> gTrack1(SAMPLE_RATE, 120, track1);
			auto pInstr1 =
				new COCBMul<FP_TYPE>(
					new COscPWM<FP_KIND>(
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							gTrack1.getOpNoteFreq()
						),
						new CGenConstant<FP_TYPE>(0.5)
					),
					new CEnvelopeADSR<FP_KIND>({ 100,100,0.8,100 }, gTrack1.getOpNoteGate())
				);

			CGenNotes<FP_KIND> gTrack2(SAMPLE_RATE, 120, track2);
			auto pInstr2 =
				new COCBMul<FP_TYPE>(
					new COscPWM<FP_KIND>(
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							gTrack2.getOpNoteFreq()
						),
						new CGenConstant<FP_TYPE>(0.5)
					),
					new CEnvelopeADSR<FP_KIND>({ 100,100,0.8,100 }, gTrack2.getOpNoteGate())
				);

			CGenNotes<FP_KIND> gTrack3(SAMPLE_RATE, 120, track3);
			auto pInstr3 =
				new COCBMul<FP_TYPE>(
					new COscTriangle<FP_KIND>(
						new COscFreq<FP_KIND>(
							SAMPLE_RATE,
							gTrack3.getOpNoteFreq()
						),
						new CGenConstant<FP_TYPE>(0.5)
					),
					new CEnvelopeADSR<FP_KIND>({ 100,100,0.8,100 }, gTrack3.getOpNoteGate())
				);

			CAudioConverter<SF_KIND, FP_KIND> genAudio(
				new COCMAdd<FP_TYPE>({
					new COCUMul<FP_TYPE>(
						0.15,
						pInstr1
					),
					new COCUMul<FP_TYPE>(
						0.15,
						pInstr2
					),
					new COCUMul<FP_TYPE>(
						0.7,
						pInstr3
					)
				})
			);

			audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 15000);

			delete pFileOut;
		};

	};
}
