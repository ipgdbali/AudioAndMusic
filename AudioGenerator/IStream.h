#pragma once

#include "type_kind.h"

namespace ipgdlib
{
	namespace stream
	{

		enum eStreamKind { eskProducer, eskConsumer };

		struct IStream :
			public ITypeKind
		{
			virtual ~IStream() {};

			virtual eStreamKind getStreamKind() const noexcept = 0;
			virtual void reset() noexcept = 0;
		};

	}

}

