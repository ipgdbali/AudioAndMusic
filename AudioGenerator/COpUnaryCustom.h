#pragma once

#include "CAbsOperatorCommonUnaryT.h"
#include <functional>

namespace ipgdlib
{
    namespace op
    {
        template <typename T>
        struct COpUnaryCustom :
            public CAbsOperatorCommonUnaryT<T>
        {
            using func_type = std::function<T(T)>;

            COpUnaryCustom(func_type func,pointer_deleter<IOperatorT<T>> operand) :
                CAbsOperatorCommonUnaryT<T>({ operand }),
                m_Function(func)
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

