#pragma once

#include "CAbsOperatorCommonBinary.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct COCBPower :
            public CAbsOperatorCommonBinary<T>
        {
            COCBAdd(pointer_deleter<IOperatorT<T>> base, pointer_deleter<IOperatorT<T>> exp) :
                CAbsOperatorCommonBinary<T>(base, exp)
            {
            }

            T get() noexcept final
            {
                return this->getLeftOperand()->get() + this->getRightOperand()->get();
            }

        };

    }
}

