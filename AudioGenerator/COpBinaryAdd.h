#pragma once

#include "CAbsOperatorCommonBinaryT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct COpBinaryAdd :
            public CAbsOperatorCommonBinaryT<T>
        {
            COpBinaryAdd(pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOperatorCommonBinaryT<T>(left, right)
            {
            }

            T get() noexcept final
            {
                return this->getLeft()->get() + this->getRight()->get();
            }

        };

    }
}

