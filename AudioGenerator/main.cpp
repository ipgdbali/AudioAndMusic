#include "eFloatingPointKind.h"

#include "CGenConstant.h"
#include "CGenNotes.h"
#include "CEnvelope.h"

#include "COscFreq.h"
#include "COscSine.h"
#include "COscPWM.h"
#include "COscTriangle.h"
#include "COscSplitter.h"

#include "CAudioConverter.h"

#include "COCURepeater.h"
#include "COCUNegate.h"
#include "COCUAdd.h"
#include "COCUMul.h"
#include "COCUCustom.h"

#include "COCBAdd.h"
#include "COCBMul.h"
#include "COCBPower.h"
#include "COCUCustom.h"

#include "COCMSerializer.h"

#include "audio.h"

using namespace ipgdlib;
using namespace ipgdlib::processor;
using namespace ipgdlib::audio;

constexpr eSampleRateKind		SAMPLE_RATE_KIND = esrk48kHz;
constexpr eFloatingPointKind	FLOATING_POINT_KIND = efpk64Bit;
constexpr eSampleFormatKind		SAMPLE_FORMAT_KIND = esfkS16Bit;

constexpr size_t				SAMPLE_RATE = sample_rate_trait<SAMPLE_RATE_KIND>::SAMPLE_PER_SECOND;
using							FLOATING_POINT_TYPE = TFPKind<FLOATING_POINT_KIND>;
using							SAMPLE_FORMAT_TYPE = typename sample_format_trait<SAMPLE_FORMAT_KIND>::type;

using namespace ipgdlib;
using namespace ipgdlib::processor;
using namespace ipgdlib::audio;

void waveform()
{
	auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("waveform.wav", esrk48kHz, 2);

	auto pFrequency = new CGenConstant<FLOATING_POINT_TYPE>(440.0);
	auto pOscilator = new COscFreq<FLOATING_POINT_KIND>(48000, pFrequency);
	auto pSignal = new COscTriangle<FLOATING_POINT_KIND>(*pOscilator,
		new CGenConstant<FLOATING_POINT_TYPE>(0.5));
	auto pStereoSignal = new COCURepeater<FLOATING_POINT_TYPE>(2, *pSignal);

	CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(
		new COCMSerializer<FLOATING_POINT_TYPE>({
			*pStereoSignal,
			new COCUNegate<FLOATING_POINT_TYPE>(*pStereoSignal)
			})
	);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pStereoSignal->setOperand(new COscPWM<FLOATING_POINT_KIND>(
		*pOscilator,
		new CGenConstant<FLOATING_POINT_TYPE>(0.5)
	)).destroy();
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pStereoSignal->setOperand(new COscSine<FLOATING_POINT_KIND>(
		*pOscilator
	)).destroy();
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pStereoSignal->setOperand(new COCUCustom<FLOATING_POINT_TYPE>(
		[](FLOATING_POINT_TYPE x) {
			return (pow(31, x) - 1) / 15.0 - 1;
		},
		*pOscilator
	)).destroy();

	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	COscSplitter<FLOATING_POINT_KIND, FLOATING_POINT_KIND, 2> sawTooth({
		[](FLOATING_POINT_TYPE x) {
			return -(pow(31, x) - 1) / 15.0 - 1;
		},
		[](FLOATING_POINT_TYPE x) {
			return (pow(31, x) - 1) / 15.0 - 1;
		}
		});
	pStereoSignal->setOperand(new COCUCustom<FLOATING_POINT_TYPE>(
		sawTooth,
		*pOscilator
	)).destroy();
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	COscSplitter<FLOATING_POINT_KIND, FLOATING_POINT_KIND, 3> Triangle3(
		{
			[](FLOATING_POINT_TYPE x) {
				return (x * x) * 2 - 1;
			},
			[](FLOATING_POINT_TYPE x) {
				return (sin(3.14159265358979323846 + x * 3.14159265358979323846) + 1) * 2 - 1;
			},
			[](FLOATING_POINT_TYPE x) {
				return ((1 - x) * (1 - x)) * 2 - 1;
			}
		},
		{ 0.1,0.9 }
	);
	pStereoSignal->setOperand(new COCUCustom<FLOATING_POINT_TYPE>(
		Triangle3,
		*pOscilator
	)).destroy();

	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	delete pOscilator;
	delete pSignal;

	delete pStereoSignal;
	delete pFileOut;

}

void notes()
{
	auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("notes.wav", esrk48kHz, 2);

	auto pFrequency = new CGenConstant<FLOATING_POINT_TYPE>(freqMap[noteSharp2IdxFreqMap["C4"]]);
	auto pOscilator = new COscFreq<FLOATING_POINT_KIND>(48000, pFrequency);
	auto pSignal = new COscPWM<FLOATING_POINT_KIND>(*pOscilator,
		new CGenConstant<FLOATING_POINT_TYPE>(0.25));
	auto pStereoSignal = new COCURepeater<FLOATING_POINT_TYPE>(2, *pSignal);

	CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(
		new COCMSerializer<FLOATING_POINT_TYPE>({
			*pStereoSignal,
			new COCUNegate<FLOATING_POINT_TYPE>(*pStereoSignal)
			})
	);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["D4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["E4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["F4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["G4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["A4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["B4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["C5"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["E4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["G4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["C4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["A4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["C5"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["F4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);

	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["C5"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["G4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["A4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["B4"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["D5"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);
	pFrequency->setConstant(freqMap[noteSharp2IdxFreqMap["C5"]]);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 500);


	delete pOscilator;
	delete pSignal;

	delete pStereoSignal;
	delete pFileOut;

}

void note_save()
{
	CNotes notes({
		{noteSharp2IdxFreqMap["C4"],1},
		{noteSharp2IdxFreqMap["D4"],1},
		{noteSharp2IdxFreqMap["E4"],1},
		{noteSharp2IdxFreqMap["F4"],1},
		{noteSharp2IdxFreqMap["G4"],1},
		{noteSharp2IdxFreqMap["A4"],1},
		{noteSharp2IdxFreqMap["B4"],1},
		{noteSharp2IdxFreqMap["C5"],1},
	});

	notes.appendNotes({
		{noteSharp2IdxFreqMap["C4"],{1,2},1},
		{noteSharp2IdxFreqMap["D4"],{1,2}},
		{noteSharp2IdxFreqMap["E4"],{1,2}},
		{noteSharp2IdxFreqMap["F4"],{1,2}},
		{noteSharp2IdxFreqMap["G4"],{1,2}},
		{noteSharp2IdxFreqMap["A4"],{1,2}},
		{noteSharp2IdxFreqMap["B4"],{1,2}},
		{noteSharp2IdxFreqMap["C5"],{1,2}},
	});
	notes.saveToFile("lagu1.notes");
}

void note_load()
{
	CNotes notes("lagu1.notes");
	CGenNotes<efpk64Bit> gNotes(48000,120,notes);

	auto pOscilator = new COscFreq<FLOATING_POINT_KIND>(48000, gNotes.getOpNoteFreq());
	auto pSignal = new COscPWM<FLOATING_POINT_KIND>(*pOscilator,
		new CGenConstant<FLOATING_POINT_TYPE>(0.5));
	auto pStereoSignal = new COCURepeater<FLOATING_POINT_TYPE>(2, *pSignal);

	CAudioConverter<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(
		new COCMSerializer<FLOATING_POINT_TYPE>({
			*pStereoSignal,
			new COCBMul<FLOATING_POINT_TYPE>(*pStereoSignal,
				new CEnvelope<FLOATING_POINT_KIND>({10000,2000,0.8,8000},gNotes.getOpNoteGate())
			)
		})
	);

	auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("waveform.wav", esrk48kHz, 2);
	audioAgregate<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio,48000 * 7);
	delete pFileOut;

}

int main(int argc, char* argv[])
{
	//note_save();
	note_load();
	return 0;
}