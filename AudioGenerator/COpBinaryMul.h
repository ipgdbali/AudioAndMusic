#pragma once

#include "CAbsOperatorCommonBinaryT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct COpBinaryMul :
            public CAbsOperatorCommonBinaryT<T>
        {

            COpBinaryMul(pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOperatorCommonBinaryT<T>(left,right)
            {
            }

            T get() noexcept final
            {
                return this->getLeftOperand()->get() * this->getRightOperand()->get();
            }

        };

    }
}

