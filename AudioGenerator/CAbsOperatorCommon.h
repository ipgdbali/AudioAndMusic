#pragma once

#include "CAbsOperator.h"
#include <vector>

namespace ipgdlib
{
    namespace processor
    {
        /// <summary>
        /// Also known as CAbsOperatorCommonMultinary
        /// </summary>
        /// <typeparam name="TIO">Input & Output Type</typeparam>
        template <typename TIO>
        struct CAbsOperatorCommon :
            public CAbsOperator<TIO>
        {

            // castUp std::vector of IOperatorT to IOperator
            static std::vector<pointer_deleter<IOperator>>
                castUp(std::vector < pointer_deleter<IOperatorT<TIO>> > operands)
            {
                std::vector<pointer_deleter<IOperator>> dest(operands.size());
                std::transform(operands.cbegin(), operands.cend(), dest.begin(),
                    [](pointer_deleter<IOperatorT<TIO>> operand) {
                        return operand.as<IOperator>();
                    }
                );
                return std::move(dest);
            }

            // castDown std::vector of IOperator to IOperatorT
            static std::vector<pointer_deleter<IOperatorT<TIO>>>
                castDown(std::vector<pointer_deleter<IOperator>> operands)
            {
                std::vector<pointer_deleter<IOperatorT<TIO>>> dest(operands.size());
                std::transform(operands.cbegin(), operands.cend(), dest.begin(),
                    [](pointer_deleter<IOperator> operand) {
                        return operand.as<IOperatorT<TIO>>();
                    }
                );
                return std::move(dest);
            }

            /// <summary>
            /// Constructor of CAbsOperatorCommon
            /// </summary>
            /// <param name="operands">
            /// Array of IOperatorT. 
            /// </param>
            CAbsOperatorCommon(std::vector<pointer_deleter<IOperatorT<TIO>>> operands) :
                CAbsOperator<TIO>(castUp(operands)) // use castUp to cast from std::vector of IOperatorT to IOperator
            {
            }

            /// <summary>
            /// change all Operands that has been set on constructor
            /// </summary>
            /// <param name="vOperands"></param>
            /// <returns></returns>
            std::vector<pointer_deleter<IOperatorT<TIO>>> setOperands(
                std::vector<pointer_deleter<IOperatorT<TIO>>> vOperands)
            {
                return castDown(CAbsOperator<TIO>::setOperands(castUp(vOperands)));
            }

            /// <summary>
            /// change single operand that has been set on constructor
            /// </summary>
            /// <param name="operand"></param>
            /// <returns></returns>
            pointer_deleter<IOperatorT<TIO>> setOperand(pointer_deleter<IOperatorT<TIO>> operand)
            {
                return CAbsOperator<TIO>::setOperand(operand.as<IOperator>()).as<IOperatorT<TIO>>();
            }

            IOperatorT<TIO>& getOperand(size_t index)
            {
                return dynamic_cast<IOperatorT<TIO>&>(
                    CAbsOperator<TIO>::getOperand(index)
                    );
            }

        protected:

            /// <summary>
            /// If in case it is needed
            /// </summary>
            /// <param name="operands"></param>
            CAbsOperatorCommon(std::vector<pointer_deleter<IOperator>> operands) :
                CAbsOperator(std::move(operands))
            {
            }

        };

        template <typename TIO>
        using CAbsOperatorCommonMultinary = CAbsOperatorCommon<TIO>;
    }
}