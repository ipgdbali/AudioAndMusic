#pragma once

#include "CAbsOperatorT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct CAbsOperatorBinaryT :
            public CAbsOperatorT<T>
        {

            using param_type = pointer_deleter<IOperatorT<T>>;

            CAbsOperatorBinaryT(pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right) :
                CAbsOperatorT<T>({ left.as<IOperator>() , right.as<IOperator>() }),
                m_Left(left), m_Right(right)
            {
            }

            void reset() noexcept override
            {
                this->m_Left->reset();
                this->m_Right->reset();
            }

        protected:
            IOperatorT<T>* getLeft() const noexcept
            {
                return this->m_Left;
            }

            IOperatorT<T>* getRight() const noexcept
            {
                return this->m_Right;
            }

        private:
            IOperatorT<T>* m_Left;
            IOperatorT<T>* m_Right;
        };

    }
}

