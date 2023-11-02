#pragma once

#include "CAbsOperatorCommonBinary.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct COCBAdd :
            public CAbsOperatorCommonBinary<T>
        {
            COCBAdd(pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOperatorCommonBinary<T>(left, right)
            {
            }

            T get() noexcept final
            {
                return this->getLeftOperand()->get() + this->getRightOperand()->get();
            }

        };

    }
}

