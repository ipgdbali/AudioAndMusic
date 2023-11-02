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
                param_type left, param_type right
            ) :
                CAbsOperatorT<T>({ left.as<IOperator>() , right.as<IOperator>() })
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
        };

    }
}

