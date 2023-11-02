#pragma once

#include "CAbsOperatorT.h"

namespace ipgdlib
{
    namespace op
    {

        template <typename TIO>
        struct CAbsOperatorCommonUnaryT :
            public CAbsOperatorT<TIO>
        {

            using param_type = pointer_deleter<IOperatorT<TIO>>;

            CAbsOperatorCommonUnaryT(param_type operand) :
                CAbsOperatorT<TIO>({ operand.as<IOperator>()})
            {
            }

        protected:
            IOperatorT<TIO>* getOperand() const noexcept
            {
                return dynamic_cast<IOperatorT<TIO>*>(this->getOperatorInput(0));
            }
        };

    }
}

