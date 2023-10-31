#pragma once

#include "IStream.h"

namespace ipgdlib
{
	namespace stream
	{
		class IStreamProducer;

		struct IStreamConsumer :
			public IStream
		{
			eStreamKind getStreamKind() const noexcept final
			{
				return eskConsumer;
			}
			
			virtual size_t getInputCount() = 0;
			virtual IStreamProducer* getInput(size_t index) = 0;
		};

	}
}

