#pragma once

#include "CAbsOperator.h"

namespace ipgdlib
{
    namespace op
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

        protected:
            IOperatorT<T>* getLeftOperand() const noexcept
            {
                return dynamic_cast<IOperatorT<T>*>((IOperator*)this->getOperand(0));
            }

            IOperatorT<T>* getRightOperand() const noexcept
            {
                return dynamic_cast<IOperatorT<T>*>((IOperator*)this->getOperand(1));
            }
        };

    }
}

