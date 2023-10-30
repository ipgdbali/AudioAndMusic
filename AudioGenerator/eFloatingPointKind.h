#pragma once

namespace ipgdlib
{

	enum eFloatingPointKind { efpk32Bit,efpk64Bit };

	template <eFloatingPointKind kind>
	using TFPKind = typename std::conditional<kind == efpk32Bit, float, double>::type;
}


