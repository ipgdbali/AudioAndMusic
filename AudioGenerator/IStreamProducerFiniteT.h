#pragma once

#include "IStreamProducerFinite.h"

namespace ipgdlib
{
    namespace stream
    {
        template <typename T>
        class IStreamProducerFiniteT :
            public IStreamProducerFinite
        {
            virtual T get() = 0;
        };

    }
}

