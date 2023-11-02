#pragma once

#include "CAbsOperatorBinaryT.h"
#include <functional>

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct COpBinaryCustom :
            public CAbsOperatorBinaryT<T>
        {
            using func_type = std::function<T(T, T)>;

            COpBinaryCustom(func_type func, pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOperatorBinaryT<T>(left, right),
                m_Function(func)
            {
            }

            func_type getFunction() const noexcept
            {
                return this->m_Function;
            }

            void setFunction(func_type func)
            {
                this->m_Function = func;
            }

            T get() noexcept final
            {
                return this->m_Function(this->getLeft(),this->getRight());
            }

        private:
            std::function<T(T, T)> m_Function;

        };

    }
}

