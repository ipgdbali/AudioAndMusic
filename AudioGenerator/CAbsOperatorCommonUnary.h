#pragma once

#include "CAbsOperator.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename TIO>
        struct CAbsOperatorCommonUnary :
            public CAbsOperatorCommonUnary<TIO>
        {

            using param_type = pointer_deleter<IOperatorT<TIO>>;

            CAbsOperatorCommonUnary(param_type operand) :
                CAbsOperatorCommonUnary<TIO>({ operand.as<IOperator>()})
            {
            }

        protected:
            IOperatorT<TIO>* getOperand() const noexcept
            {
                return dynamic_cast<IOperatorT<TIO>*>(
                    (IOperator*)CAbsOperatorCommonUnary<TIO>::getOperand(0)
                );
            }
        };

    }
}

