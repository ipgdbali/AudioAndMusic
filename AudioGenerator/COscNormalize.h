#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COscNormalize :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;

            COscNormalize(pointer_deleter<IOperatorT<float_type>> operand) :
                CAbsOperatorCommonUnary<float_type>(std::move(operand))
            {
            }

            float_type get() noexcept final
            {
                return (this->getOperand().get() + 1.0) / 2.0;
            }

        };

    }
}

