#pragma once

#include "CAbsOpBinaryT.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct COpAdd :
            public CAbsOpBinaryT<T>
        {
            COpAdd(pointer_deleter<IProcessorT<T>> left, pointer_deleter<IProcessorT<T>> right) :
                CAbsOpBinaryT<T>({ left, right})
            {
            }

            T get() noexcept final
            {
                return this->getLeft->get() + this->getRight->get();
            }

        };

    }
}

