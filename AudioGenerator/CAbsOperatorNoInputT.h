#pragma once

#include "IOperatorT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename TOutput>
        struct CAbsOperatorNoInputT :
            public IOperatorT<TOutput>
        {

            size_t getOperatorInputCount()
            {
                return 0;
            }

        };

    }
}


