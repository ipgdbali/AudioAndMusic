#pragma once

#include "IStream.h"

namespace ipgdlib
{
	namespace stream
	{
		class IStreamConsumer;

		struct IStreamProducer :
			public IStream
		{
			eStreamKind getStreamKind() const noexcept final
			{
				return eskProducer;
			}

			virtual size_t getInputStreamCount() const noexcept = 0;
			virtual IStreamProducer getInputStream(size_t index)
		};

	}
}

