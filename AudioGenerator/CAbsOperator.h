#pragma once

#include "IOperator.h"
#include "IOperatorT.h"
#include "pointer_deleter.h"
#include <vector>
#include <algorithm>

namespace ipgdlib
{
    namespace processor
    {

        template <typename TOutput>
        struct CAbsOperator :
            public IOperatorT<TOutput>
        {

            using ret_type = TOutput;

            ~CAbsOperator()
            {
                this->destroy();
            }

            CAbsOperator(std::vector<pointer_deleter<IOperator>> operands) :
                m_vOperands(std::move(operands))
            {
            }

            void reset() noexcept override
            {
                // reset all operand
                std::for_each(m_vOperands.begin(), m_vOperands.end(), [](pointer_deleter<IOperator> x) {
                    x->reset();
                });
            }

            size_t getOperandCount() const noexcept final
            {
                // return number of operator's input (operand)
                return this->m_vOperands.size();
            }

            std::vector<pointer_deleter<IOperator>> setOperands(std::vector<pointer_deleter<IOperator>> vOperands)
            {
                std::vector<pointer_deleter<IOperator>> ret;
                if (vOperands.size() > 0)
                {
                    ret = std::move(this->m_vOperands);
                    this->m_vOperands = std::move(m_vOperands);
                }
                return ret;
            }

            pointer_deleter<IOperator> setOperand(size_t index, pointer_deleter<IOperator> operand)
            {
                pointer_deleter<IOperator> ret;

                ret = std::move(this->m_vOperands[index]);
                this->m_vOperands[index] = std::move(operand);

                return ret;
            }

        protected:

            IOperator& getOperand(size_t index)
            {
                return *this->m_vOperands[index];
            }

            std::vector<pointer_deleter<IOperator>> &getOperands()
            {
                return this->m_vOperands;
            }

            void destroy()
            {
                std::for_each(m_vOperands.begin(), m_vOperands.end(), [](pointer_deleter<IOperator> x) {
                    x.destroy();
                });
            }

        protected:
            std::vector<pointer_deleter<IOperator>> m_vOperands;
        };

    }
}


