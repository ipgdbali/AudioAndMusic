#pragma once

#include "CAbsOpUnaryT.h"

namespace ipgdlib
{
    namespace processor
    {
        template <typename T>
        struct COpNegate :
            public CAbsOpUnaryT<T>
        {
            COpNegate(pointer_deleter<IProcessorT<T>> operand) :
                CAbsOpUnaryT<T>({ operand.as<IProcessor>()})
            {
            }

            T get() noexcept final
            {
                return -this->getOperand();
            }

        };

    }
}

