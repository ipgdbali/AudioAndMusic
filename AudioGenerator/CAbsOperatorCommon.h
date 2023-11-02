#pragma once

#include "CAbsOperator.h"

namespace ipgdlib
{
    namespace op
    {
        /// <summary>
        /// Also known as CAbsOperatorCommonMultinary
        /// </summary>
        /// <typeparam name="TIO"></typeparam>
        template <typename TIO>
        struct CAbsOperatorCommon :
            public CAbsOperatorCommonUnary<TIO>
        {

            static std::vector<pointer_deleter<IOperator>>
                conv(std::vector < pointer_deleter<IOperatorT<TIO>> > operands)
            {
                std::vector<pointer_deleter<IOperator>> dest(operands.size());
                std::transform(operands.cbegin(), operands.cend(), dest.begin(),
                    [](pointer_deleter<IOperatorT<T>> operand) {
                        return operand.as<IOperator>();
                    }
                );
                return std::move(dest);
            }

            CAbsOperatorCommon(std::initializer_list<pointer_deleter<IOperatorT<TIO>>> operands) :
                CAbsOperatorCommonUnary<TIO>(conv(operands))
            {
            }

            CAbsOperatorCommon(std::vector<pointer_deleter<IOperatorT<TIO>>> operands) :
                CAbsOperatorCommonUnary<TIO>(conv(operands))
            {
            }

        protected:

            CAbsOperatorCommon(std::initializer_list<pointer_deleter<IOperator>> operands) :
                m_vInput(std::move(operands))
            {
            }

            CAbsOperatorCommon(std::vector<pointer_deleter<IOperator>> operands) :
                m_vInput(std::move(operands))
            {
            }

            IOperatorT<TIO>* getOperand(size_t index) const
            {
                return dynamic_cast<IOperatorT<TIO>*>(
                    (IOperator*)this->getOperand(index)
                );
            }

        };

        template <typename TIO>
        using CAbsOperatorCommonMultinary = CAbsOperatorCommon<TIO>;
    }
}