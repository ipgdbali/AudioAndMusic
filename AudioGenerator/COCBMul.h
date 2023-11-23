#pragma once

#include "CAbsOperatorCommonBinary.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct COCBMul :
            public CAbsOperatorCommonBinary<T>
        {

            COCBMul(pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOperatorCommonBinary<T>(left,right)
            {
            }

            T get() noexcept final
            {
                return this->getLeftOperand().get() * this->getRightOperand().get();
            }

        };

    }
}

