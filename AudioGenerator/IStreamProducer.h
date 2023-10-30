#pragma once

#include "IStream.h"

namespace ipgdlib
{
	namespace stream
	{

		struct IStreamProducer :
			public IStream
		{
			eStreamKind getStreamKind() const noexcept final
			{
				return eskProducer;
			}
		};

	}
}

