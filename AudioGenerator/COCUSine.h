#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{
    namespace op
    {

        template <eFloatingPointKind fpk>
        struct COCUSine :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using ret_type = float_type;

            COCUSine(pointer_deleter<IOperatorT<float_type>> opOsc) :
                CAbsOperatorCommonUnary<float_type>({ opOsc.as<IOperator>() })
            {
            }

            ret_type get() noexcept final
            {
                if constexpr (fpk == efpk32Bit)
                    return sinf(this->getOperand()->get());
                else
                    return sin(this->getOperand()->get());
            }

        };

    }
}

