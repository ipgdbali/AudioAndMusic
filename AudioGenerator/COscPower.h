#pragma once

#include "CAbsOperatorCommonBinary.h"
#include "IOperatorT.h"
#include "eFloatingPointKind.h"
#include "pointer_deleter.h"
#include <utility>

namespace ipgdlib
{
    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COscPower :
            public CAbsOperatorCommonBinary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using ret_type = float_type;

            COscPower(
                pointer_deleter<IOperatorT<float_type>> opOsc,
                pointer_deleter<IOperatorT<float_type>> opDutyCycle
            ) :
                CAbsOperatorCommonBinary<float_type>(opOsc, opDutyCycle)
            {
            }

            ret_type get() noexcept final
            {

                float_type osc = this->getLeftOperand().get();
                float_type duty = this->getRightOperand().get();

                return pow(osc, duty) * 2 - 1;
            }

        };

    }
}

