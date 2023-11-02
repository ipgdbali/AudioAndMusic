#pragma once

#include "CAbsOperatorBinaryT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct COpBinaryMul :
            public CAbsOperatorBinaryT<T>
        {

            COpBinaryMul(pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOperatorBinaryT<T>(left,right)
            {
            }

            T get() noexcept final
            {
                return this->getLeft()->get() * this->getRight()->get();
            }

        };

    }
}

