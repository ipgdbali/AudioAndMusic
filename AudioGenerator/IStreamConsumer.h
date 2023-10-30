#pragma once

#include "IStream.h"

namespace ipgdlib
{
	namespace stream
	{

		struct IStreamConsumer :
			public IStream
		{
			eStreamKind getStreamKind() const noexcept final
			{
				return eskConsumer;
			}
		};

	}
}

