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
	auto pFreq = 
	new CGenFPFrequency<FLOATING_POINT_KIND>(SAMPLE_RATE,
		new CModOffset<FLOATING_POINT_TYPE>(440,
			new CModMul<FLOATING_POINT_TYPE>(20,
				new CGenLinear<FLOATING_POINT_KIND>(
					new CGenFPFrequency<FLOATING_POINT_KIND>(SAMPLE_RATE,
						new CGenConstant<FLOATING_POINT_TYPE>(1)
					)
				)
			)
		)
	);

	// std::pair return error
	for(size_t li = 0; li < 48000;li++)
		std::cout << li << '\t' << pFreq->get().first << '\t' << pFreq->get().second << std::endl;




	return 0;
}