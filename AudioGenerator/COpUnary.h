#pragma once

#include "CAbsOpUnaryT.h"
#include <functional>

namespace ipgdlib
{
    namespace processor
    {
        template <typename T>
        class COpUnary :
            public CAbsOpUnaryT<T>
        {
            using func_type = std::function<T(T)>;

            COpUnary(func_type func,pointer_deleter<IProcessorT<T>> operand) :
                CAbsOpUnaryT<T>({ operand.as<IProcessor>() }),
                m_Function(func),
                m_Operand(operand)
            {
            }

            func_type getFunction() const noexcept
            {
                return this->m_Function;
            }

            void setFunction(func_type func) noexcept
            {
                this->m_Function = func;
            }

            T get() noexcept final
            {
                return this->m_Function(this->getOperand()->get());
            }

        private:
            std::function<T(T)>     m_Function;
        };

    }
}

