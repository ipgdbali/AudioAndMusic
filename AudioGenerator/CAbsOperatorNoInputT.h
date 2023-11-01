#pragma once

#include "IOperatorT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct CAbsOperatorNoInputT :
            public IOperatorT<T>
        {

            size_t getOperatorInputCount()
            {
                return 0;
            }

        };

    }
}


