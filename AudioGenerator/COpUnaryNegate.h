#pragma once

#include "CAbsOpUnaryT.h"

namespace ipgdlib
{
    namespace op
    {
        template <typename T>
        struct COpUnaryNegate :
            public CAbsOpUnaryT<T>
        {
            COpUnaryNegate(pointer_deleter<IOperatorT<T>> operand) :
                CAbsOpUnaryT<T>({ operand })
            {
            }

            T get() noexcept final
            {
                return -this->getOperand()->get();
            }

        };

    }
}

