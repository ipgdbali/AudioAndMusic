#include <iostream>
#include <iomanip>

#include "CGenConstant.h"
#include "CGenFrequency.h"
#include "CGenFunc.h"
#include "CDuplicator.h"
#include "CModFunc.h"
#include "CFuncSerialize.h"
#include "CConvAudio.h"

#include "eFloatingPointKind.h"
#include "audio.h"

using namespace ipgdlib;
using namespace ipgdlib::stream;
using namespace ipgdlib::audio;

constexpr eSampleRateKind		SAMPLE_RATE_KIND = esrk48kHz;
constexpr eFloatingPointKind	FLOATING_POINT_KIND = efpk64Bit;
constexpr eSampleFormatKind		SAMPLE_FORMAT_KIND = esfkS16Bit;

constexpr size_t				SAMPLE_RATE = sample_rate_trait<SAMPLE_RATE_KIND>::SAMPLE_PER_SECOND;
using							FLOATING_POINT_TYPE = TFPKind<FLOATING_POINT_KIND>;
using							SAMPLE_FORMAT_TYPE = typename sample_format_trait<SAMPLE_FORMAT_KIND>::type;

int main(int argc, char* argv[])
{
	CDuplicator<std::pair<FLOATING_POINT_TYPE,bool>> genFreq(2,
		new CGenFPFrequency<FLOATING_POINT_KIND>(SAMPLE_RATE,
			new CGenConstant<FLOATING_POINT_TYPE>(440)
		)
	);

	CConvAudio<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> signal({
		new CFuncSerialize<FLOATING_POINT_TYPE>({
			new CGenSine<FLOATING_POINT_KIND>({ &genFreq,false }),
			new CGenPWM<FLOATING_POINT_KIND>({ &genFreq,false },new CGenConstant<FLOATING_POINT_TYPE>(0.3)),
		})
	});

	auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("output.wav", SAMPLE_RATE_KIND, 2);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>({ pFileOut }, { &signal ,false }, 1000);
	delete pFileOut;

	return 0;
}