#pragma once

#include "CAbsOperatorT.h"
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
            public CAbsOperatorT<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using param_type = pointer_deleter<IOperatorT<float_type>>;
            using ret_type = float_type;

            COscPWM(param_type opOsc,param_type opDutyCycle) :
                CAbsOperatorT<float_type>(
                    { opOsc.as<IOperator>(),opDutyCycle.as<IOperator>()}),
                m_Osc(opOsc),m_DutyCycle(opDutyCycle)
            {
            }

            ret_type get() noexcept final
            {
                if (this->m_Osc->get() < this->m_DutyCycle->get())
                    return 1.0;
                else
                    return -1.0;
            }

        private:
            IOperatorT<float_type>* m_Osc;
            IOperatorT<float_type>* m_DutyCycle;

        };

    }
}

