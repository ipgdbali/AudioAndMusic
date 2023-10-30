#pragma once

#include "IStreamConsumer.h"
#include "IStreamProducerT.h"

namespace ipgdlib
{
	namespace stream
	{
		template <typename T>
		struct IStreamConsumerT :
			public IStreamConsumer
		{
			virtual IStreamProducerT<T>* getStreamProducer() const noexcept = 0;
		};

	}
}


