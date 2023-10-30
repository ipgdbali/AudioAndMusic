#pragma once

#include "IGenerator.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{
	namespace generator
	{

		template<eFloatingPointKind kind>
		struct CGenSinosoid :
			public CAbsGenerator<TFPKind<kind>>
		{
			using type = TFPKind<kind>;

			type get() const noexcept final
			{

			}

			private:
				type m_Phase;
				type m_PhaseIncrement;
		};

	}


}

