#pragma once

#include "CAbsOperatorCommonUnary.h"

namespace ipgdlib
{
    namespace processor
    {
        template <typename T>
        struct COCUNegate :
            public CAbsOperatorCommonUnary<T>
        {
            COCUNegate(pointer_deleter<IOperatorT<T>> operand) :
                CAbsOperatorCommonUnary<T>({ operand })
            {
            }

            T get() noexcept final
            {
                return -this->getOperand().get();
            }

        };

    }
}

