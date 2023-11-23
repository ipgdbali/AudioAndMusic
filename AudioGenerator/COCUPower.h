#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COCUPower :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using type = TFPKind<fpk>;

            COCUPower(type exp,pointer_deleter<IOperatorT<type>> operand) :
                m_Exponent(exp),CAbsOperatorCommonUnary<type>({ operand.as<IOperator>() })
            {
            }

            T get() noexcept final
            {
                return pow(this->getOperand(),this->m_Exponent);
            }

            type getExponent() const noexcept
            {
                return this->m_Exponent;
            }

            void setExponent(type exp)
            {
                this->m_Exponent = exp;
            }

        private:
            type    m_Exponent;

        };

    }
}

