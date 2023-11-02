#pragma once

#include "IOperator.h"
#include "IOperatorT.h"
#include "pointer_deleter.h"
#include <vector>
#include <algorithm>

namespace ipgdlib
{
    namespace op
    {

        template <typename TOutput>
        struct CAbsOperator :
            public IOperatorT<TOutput>
        {

            using ret_type = TOutput;

            ~CAbsOperator()
            {
                for (auto i : this->m_vInput)
                    i.execute();
            }

            CAbsOperator(std::initializer_list<pointer_deleter<IOperator>> operands) :
                m_vInput(std::move(operands))
            {
            }

            CAbsOperator(std::vector<pointer_deleter<IOperator>> operands) :
                m_vInput(std::move(operands))
            {
            }

            void reset() noexcept override
            {
                for (auto& i : this->m_vInput)
                    i->reset();
            }

            size_t getOperandCount()
            {
                return this->m_vInput.size();
            }

        protected:
            IOperator* getOperand(size_t index) const
            {
                return this->m_vInput[index];
            }

        private:
            std::vector<pointer_deleter<IOperator>> m_vInput;
        };

    }
}


