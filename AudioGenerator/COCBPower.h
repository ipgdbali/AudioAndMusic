#pragma once

#include "eFloatingPointKind.h"
#include "CAbsOperatorCommonBinary.h"
#include <cmath>

namespace ipgdlib
{
    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COCBPower :
            public CAbsOperatorCommonBinary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;

            COCBPower(pointer_deleter<IOperatorT<float_type>> base, pointer_deleter<IOperatorT<float_type>> exp) :
                CAbsOperatorCommonBinary<float_type>(base, exp)
            {
            }

            float_type get() noexcept final
            {
                return std::pow(this->getLeftOperand()->get(),this->getRightOperand()->get());
            }

        };

    }
}

