#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COscUnNormalize :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;

            COscUnNormalize(pointer_deleter<IOperatorT<float_type>> operand) :
                CAbsOperatorCommonUnary<float_type>(std::move(operand))
            {
            }

            float_type get() noexcept final
            {
                return this->getOperand().get() * 2.0 - 1.0;
            }

        };

    }
}

