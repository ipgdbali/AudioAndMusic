#pragma once

#include "CAbsOperatorCommonUnary.h"

namespace ipgdlib
{
    namespace op
    {
        template <typename T>
        struct COCUMul :
            public CAbsOperatorCommonUnary<T>
        {
            COCUMul(T base, pointer_deleter<IOperatorT<T>> operand) :
                CAbsOperatorCommonUnary<T>({ operand }),
                m_Base(base)
            {
            }

            T getBase() const noexcept
            {
                return this->m_Base;
            }

            void setBase(T base)
            {
                this->m_Base = base;
            }

            T get() noexcept final
            {
                return this->m_Base * this->getOperand()->get();
            }

        private:
            T m_Base;
        };

    }
}

