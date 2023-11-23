#pragma once

#include "IOperatorT.h"

namespace ipgdlib
{
    namespace processor
    {

        /// <summary>
        /// Operator that has no Operator
        /// </summary>
        /// <typeparam name="TOutput"></typeparam>
        template <typename TOutput>
        struct CAbsOperatorGenerator :
            public IOperatorT<TOutput>
        {

            size_t getOperandCount() const noexcept final
            {
                return 0;
            }

        };

        template <typename TOutput>
        using CAbsGenerator = CAbsOperatorGenerator<TOutput>;
    
    }
}


