#pragma once

#include "CAbsOperator.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename TIO>
        struct CAbsOperatorCommonUnary :
            public CAbsOperator<TIO>
        {

            using param_type = pointer_deleter<IOperatorT<TIO>>;

            CAbsOperatorCommonUnary(param_type operand) :
                CAbsOperator<TIO>({ operand.as<IOperator>()})
            {
            }

            pointer_deleter<IOperatorT<TIO>> setOperand(pointer_deleter<IOperatorT<TIO>> operand)
            {
                return CAbsOperator<TIO>::setOperand(0, std::move((IOperator*)operand)).as<IOperatorT<TIO>>();
            }

            IOperatorT<TIO> &getOperand() noexcept
            {
                return dynamic_cast<IOperatorT<TIO>&>(
                    CAbsOperator<TIO>::getOperand(0)
                );
            }
        };

    }
}

