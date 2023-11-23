#pragma once

#include <type_traits>

namespace ipgdlib
{
	enum eFloatingPointKind { efpk32Bit,efpk64Bit };

	template <eFloatingPointKind kind>
	using TFPKind = std::conditional<kind == efpk32Bit, float, double>::type;
}


