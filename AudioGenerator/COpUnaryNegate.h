#pragma once

#include "CAbsOperatorCommonUnaryT.h"

namespace ipgdlib
{
    namespace op
    {
        template <typename T>
        struct COpUnaryNegate :
            public CAbsOperatorCommonUnaryT<T>
        {
            COpUnaryNegate(pointer_deleter<IOperatorT<T>> operand) :
                CAbsOperatorCommonUnaryT<T>({ operand })
            {
            }

            T get() noexcept final
            {
                return -this->getOperand()->get();
            }

        };

    }
}

