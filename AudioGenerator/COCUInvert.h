#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COCUInvert :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;

            COCUInvert(pointer_deleter<IOperatorT<float_type>> operand) :
                CAbsOperatorCommonUnary<float_type>(std::move(operand))
            {
            }

            float_type get() noexcept final
            {
                return (float_type)1.0 - this->getOperand().get();
            }

        };

    }
}

