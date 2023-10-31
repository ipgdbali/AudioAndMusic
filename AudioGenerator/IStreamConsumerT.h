#pragma once

#include "IStreamConsumer.h"
#include "wrap_param.h"

namespace ipgdlib
{
	namespace stream
	{
		template <typename T>
		struct IStreamConsumerT :
			public IStreamConsumer
		{
			virtual IStreamProducerT<T>* getInput(size_t index) const = 0;
		};

	}
}


