#pragma once

#include "CAbsOperatorT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct CAbsOperatorCommonBinaryT :
            public CAbsOperatorT<T>
        {

            using param_type = pointer_deleter<IOperatorT<T>>;

            CAbsOperatorCommonBinaryT(
                pointer_deleter<IOperatorT<T>> left, pointer_deleter<IOperatorT<T>> right
            ) :
                CAbsOperatorT<T>({ left.as<IOperator>() , right.as<IOperator>() }),
                m_Left(left), m_Right(right)
            {
            }

        protected:
            IOperatorT<T>* getLeftOperand() const noexcept
            {
                return dynamic_cast<IOperatorT<T>*>(this->getOperatorInput(0));
            }

            IOperatorT<T>* getRightOperand() const noexcept
            {
                return dynamic_cast<IOperatorT<T>*>(this->getOperatorInput(1));
            }

        private:
            IOperatorT<T>* m_Left;
            IOperatorT<T>* m_Right;
        };

    }
}

