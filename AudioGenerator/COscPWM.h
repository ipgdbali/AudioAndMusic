#pragma once

#include "CAbsOperatorCommonBinary.h"
#include "IOperatorT.h"
#include "eFloatingPointKind.h"
#include "pointer_deleter.h"
#include <utility>

namespace ipgdlib
{
    namespace op
    {

        template <eFloatingPointKind fpk>
        struct COscPWM :
            public CAbsOperatorCommonBinary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using param_type = pointer_deleter<IOperatorT<float_type>>;
            using ret_type = float_type;

            COscPWM(param_type opOsc,param_type opDutyCycle) :
                CAbsOperatorCommonBinary<float_type>(opOsc,opDutyCycle)
            {
            }

            ret_type get() noexcept final
            {
                if (this->getLeftOperand()->get() < this->getRightOperand()->get())
                    return 1.0;
                else
                    return -1.0;
            }

        };

    }
}

