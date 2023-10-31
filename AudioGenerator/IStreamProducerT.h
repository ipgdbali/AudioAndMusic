#pragma once

#include "IStreamProducer.h"

namespace ipgdlib
{
	namespace stream
	{
		template <typename T>
		struct IStreamProducerT :
			public IStreamProducer
		{
			virtual T get() noexcept = 0;
		};

	}
}