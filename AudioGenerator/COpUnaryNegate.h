#pragma once

#include "CAbsOperatorUnaryT.h"

namespace ipgdlib
{
    namespace op
    {
        template <typename T>
        struct COpUnaryNegate :
            public CAbsOperatorUnaryT<T>
        {
            COpUnaryNegate(pointer_deleter<IOperatorT<T>> operand) :
                CAbsOperatorUnaryT<T>({ operand })
            {
            }

            T get() noexcept final
            {
                return -this->getOperand()->get();
            }

        };

    }
}

