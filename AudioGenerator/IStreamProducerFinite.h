#pragma once
#include "IStreamProducer.h"

namespace ipgdlib
{
    namespace stream
    {

        class IStreamProducerFinite :
            public IStreamProducer
        {
            virtual size_t getLength() const noexcept = 0;
        };

    }
}

