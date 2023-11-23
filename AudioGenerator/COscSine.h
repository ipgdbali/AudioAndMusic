#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "IOperatorT.h"
#include "eFloatingPointKind.h"
#include "pointer_deleter.h"
#include <utility>

namespace ipgdlib
{
    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COscSine :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using ret_type = float_type;

            COscSine(pointer_deleter<IOperatorT<float_type>> opOsc) : 
                CAbsOperatorCommonUnary<float_type>(opOsc)
            {
            }

            ret_type get() noexcept final
            {
                if constexpr (fpk == efpk32Bit)
                    return sinf(this->getOperand().get() * 3.14159265358979323846 * 2);
                else
                    return sin(this->getOperand().get() * 3.14159265358979323846 * 2);
            }

        };

    }
}

