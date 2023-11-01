#include <iostream>
#include <iomanip>

#include "CGenConstant.h"
#include "COscillator.h"
#include "CFuncFork.h"
#include "COscSine.h"
#include "COscPWM.h"
#include "COscTriangle2.h"
#include "CFuncSerializer.h"
#include "CFuncConvAudio.h"

#include "COpUnaryCustom.h"

#include "eFloatingPointKind.h"
#include "audio.h"

using namespace ipgdlib;
using namespace ipgdlib::op;
using namespace ipgdlib::audio;

constexpr eSampleRateKind		SAMPLE_RATE_KIND = esrk48kHz;
constexpr eFloatingPointKind	FLOATING_POINT_KIND = efpk64Bit;
constexpr eSampleFormatKind		SAMPLE_FORMAT_KIND = esfkS16Bit;

constexpr size_t				SAMPLE_RATE = sample_rate_trait<SAMPLE_RATE_KIND>::SAMPLE_PER_SECOND;
using							FLOATING_POINT_TYPE = TFPKind<FLOATING_POINT_KIND>;
using							SAMPLE_FORMAT_TYPE = typename sample_format_trait<SAMPLE_FORMAT_KIND>::type;

using namespace ipgdlib;
using namespace ipgdlib::op;

int main(int argc, char* argv[])
{
	CFuncFork< std::pair<FLOATING_POINT_TYPE,bool> > fork(2,
		new COscillator<FLOATING_POINT_KIND>(SAMPLE_RATE,
			new CGenConstant<FLOATING_POINT_TYPE>(440)
		)
	);

	CFuncFork< FLOATING_POINT_TYPE> modDutyCycle(2,
		new COpUnaryCustom<FLOATING_POINT_TYPE>(
			[](double x) {
				return 0.5 + 0.3 * x;
			},
			new COscSine<FLOATING_POINT_KIND>(
				new COscillator<FLOATING_POINT_KIND>(SAMPLE_RATE,
					new CGenConstant<FLOATING_POINT_TYPE>(1)
				)
			)
		)
	);

	CFuncConvAudio<SAMPLE_FORMAT_KIND, FLOATING_POINT_KIND> genAudio(
		new CFuncSerializer<FLOATING_POINT_TYPE>({
			new COscTriangle2<FLOATING_POINT_KIND>(fork,
				modDutyCycle
			),
			new COscPWM<FLOATING_POINT_KIND>(fork,
				modDutyCycle
			)
		})
	);

	auto pFileOut = new CWaveFileWriter<SAMPLE_FORMAT_KIND>("output.wav", esrk48kHz, 2);
	audioAgregateMillis<SAMPLE_FORMAT_TYPE>(pFileOut, genAudio, 5000);
	delete pFileOut;
	return 0;
}