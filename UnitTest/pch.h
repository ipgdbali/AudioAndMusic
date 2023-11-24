// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here

#include "../AudioGenerator/eFloatingPointKind.h"
#include "../AudioGenerator/CGenConstant.h"
#include "../AudioGenerator/CGenFiniteConstant.h"

#include "../AudioGenerator/CEnvelope.h"

#include "../AudioGenerator/audio.h"
#include "../AudioGenerator/function.h"

#include "../AudioGenerator/CAudioConverter.h"

#include "../AudioGenerator/COscFreq.h"
#include "../AudioGenerator/COscNoise.h"
#include "../AudioGenerator/COscPWM.h"
#include "../AudioGenerator/COscSine.h"
#include "../AudioGenerator/COscTriangle.h"
#include "../AudioGenerator/COscPower.h"
#include "../AudioGenerator/COscExponent.h"

#include "../AudioGenerator/COscNormalize.h"
#include "../AudioGenerator/COscUnNormalize.h"

#include "../AudioGenerator/COCUInvert.h"
#include "../AudioGenerator/COCUCustom.h"
#include "../AudioGenerator/COCUMul.h"

#include "../AudioGenerator/COCBMul.h"


using namespace ipgdlib;
using namespace ipgdlib::processor;
using namespace ipgdlib::audio;

constexpr eSampleRateKind		SAMPLE_RATE_KIND = esrk48kHz;
constexpr eFloatingPointKind	FLOATING_POINT_KIND = efpk64Bit;
constexpr eSampleFormatKind		SAMPLE_FORMAT_KIND = esfkS16Bit;

constexpr size_t				SAMPLE_RATE = sample_rate_trait<SAMPLE_RATE_KIND>::SAMPLE_PER_SECOND;
using							FLOATING_POINT_TYPE = TFPKind<FLOATING_POINT_KIND>;
using							SAMPLE_FORMAT_TYPE = typename sample_format_trait<SAMPLE_FORMAT_KIND>::type;


#endif //PCH_H
