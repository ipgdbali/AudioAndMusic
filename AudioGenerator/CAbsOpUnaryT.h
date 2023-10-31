#pragma once

#include "CAbsProcessorT.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct CAbsOpUnaryT :
            public CAbsProcessorT<T>
        {

            CAbsOpUnaryT(pointer_deleter<IProcessorT<T>> operand) :
                CAbsProcessorT<T>({ operand }),
                m_Operand(operand)
            {
            }

            void reset() noexcept override
            {
                this->m_Operand->reset();
            }

        protected:
            IProcessorT<T>* getOperand() const noexcept
            {
                return this->m_Operand;
            }

        private:
            IProcessorT<T>* m_Operand;
        };

    }
}

