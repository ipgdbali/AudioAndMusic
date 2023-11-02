#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace op
    {

        template <eFloatingPointKind fpk>
        struct COCUExponent :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using type = TFPKind<fpk>;

            COCUExponent(type base, pointer_deleter<IOperatorT<type>> operand) :
                m_Base(base), CAbsOperatorCommonUnary<type>({ operand.as<IOperator>() })
            {
            }

            T get() noexcept final
            {
                return pow(this->m_Base,this->getOperand());
            }

            type getBase() const noexcept
            {
                return this->m_Base;
            }

            void setBase(type base)
            {
                this->m_Base = base;
            }

        private:
            type    m_Base;

        };

    }
}

