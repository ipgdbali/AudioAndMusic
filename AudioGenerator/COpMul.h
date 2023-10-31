#pragma once

#include "CAbsOpBinaryT.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct COpMul :
            public CAbsOpBinaryT<T>
        {

            COpMul(pointer_deleter<IProcessorT<T>> left, pointer_deleter<IProcessorT<T>> right) :
                CAbsOpBinaryT<T>(left,right)
            {
            }

            T get() noexcept final
            {
                return this->getLeft() * this->getRight();
            }

        };

    }
}

