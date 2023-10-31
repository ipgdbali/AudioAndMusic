#pragma once

#include "IProcessorT.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct CAbsProcessorNoInputT :
            public IProcessorT<T>
        {

            size_t getProcessorInputCount()
            {
                return 0;
            }

        };

    }
}


