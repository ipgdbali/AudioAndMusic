#pragma once

#include "CAbsOpUnaryT.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace op
    {

        template <eFloatingPointKind fpk>
        struct COpUnaryPower :
            public CAbsOpUnaryT<TFPKind<fpk>>
        {
            using type = TFPKind<fpk>;

            COpUnaryPower(type exp,pointer_deleter<IOperatorT<type>> operand) :
                m_Exponent(exp),CAbsOpUnaryT<type>({ operand.as<IOperator>() })
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
