#pragma once

#include "CAbsOperatorGenerator.h"
#include "eFloatingPointKind.h"
#include <ctime>
#include <cstdlib>

namespace ipgdlib
{
	namespace processor
	{

		template <eFloatingPointKind fpKind>
		struct COscNoise :
			public CAbsOperatorGenerator<TFPKind<fpKind>>
		{
			using float_type = TFPKind<fpKind>;
			
			COscNoise()
			{
			}

			void reset() noexcept final
			{
				std::srand(std::time(0));
			}

			float_type get() noexcept final
			{
				return (((float_type)std::rand() / RAND_MAX) - 0.5) * 2;
			}

		};

	}

};

