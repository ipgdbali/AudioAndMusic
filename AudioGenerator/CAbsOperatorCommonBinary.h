#pragma once

#include "CAbsOperator.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct CAbsOperatorCommonBinary :
            public CAbsOperator<T>
        {

            using param_type = pointer_deleter<IOperatorT<T>>;

            CAbsOperatorCommonBinary(
                param_type left, param_type right
            ) :
                CAbsOperator<T>({ left.as<IOperator>() , right.as<IOperator>() })
            {
            }

            pointer_deleter<IOperatorT<T>> setLeftOperand(pointer_deleter<IOperatorT<T>> leftOperand)
            {
                return this->setOperand(0, std::move(leftOperand)).as<IOperatorT<T>>();
            }
            pointer_deleter<IOperatorT<T>> setRightOperand(pointer_deleter<IOperatorT<T>> rightOperand)
            {
                return this->setOperand(1, std::move(rightOperand)).as<IOperatorT<T>>();
            }

        protected:
            IOperatorT<T> &getLeftOperand() noexcept
            {
                return dynamic_cast<IOperatorT<T>&>(this->getOperand(0));
            }

            IOperatorT<T> &getRightOperand() noexcept
            {
                return dynamic_cast<IOperatorT<T>&>(this->getOperand(1));
            }
        };

    }
}

