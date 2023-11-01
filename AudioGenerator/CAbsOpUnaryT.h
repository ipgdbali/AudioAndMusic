#pragma once

#include "CAbsOperatorT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct CAbsOpUnaryT :
            public CAbsOperatorT<T>
        {

            using param_type = pointer_deleter<IOperatorT<T>>;

            CAbsOpUnaryT(param_type operand) :
                CAbsOperatorT<T>({ operand.as<IOperator>()}),
                m_Operand(operand)
            {
            }

            void reset() noexcept override
            {
                this->m_Operand->reset();
            }

        protected:
            IOperatorT<T>* getOperand() const noexcept
            {
                return this->m_Operand;
            }

        private:
            IOperatorT<T>* m_Operand;
        };

    }
}

