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
        struct COscTriangle2 :
            public CAbsOperatorT<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using ret_type = float_type;

            COscTriangle2(
                pointer_deleter<IOperatorT<std::pair<float_type, bool>>> opOsc,
                pointer_deleter<IOperatorT<float_type>> opDutyCycle
            ) :
                CAbsOperatorT<float_type>({ opOsc.as<IOperator>(),opDutyCycle.as<IOperator>() }), 
                m_Osc(opOsc), m_DutyCycle(opDutyCycle)
            {
            }

            ret_type get() noexcept final
            {

                float_type osc = this->m_Osc->get().first;
                float_type duty = this->m_DutyCycle->get();

                if (osc < duty)
                    return osc / duty * 2 - 1;
                else
                    return -((osc - duty) / (1-duty) * 2 - 1);
            }

        private:
            IOperatorT<std::pair<float_type, bool>>* m_Osc;
            IOperatorT<float_type>* m_DutyCycle;

        };

    }
}

