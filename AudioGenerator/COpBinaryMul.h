#pragma once

#include "CAbsOpBinaryT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct COpBinaryMul :
            public CAbsOpBinaryT<T>
        {

            COpBinaryMul(pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOpBinaryT<T>(left,right)
            {
            }

            T get() noexcept final
            {
                return this->getLeft()->get() * this->getRight()->get();
            }

        };

    }
}

