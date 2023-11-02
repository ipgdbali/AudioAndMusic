#pragma once

#include "IOperator.h"
#include "IOperatorT.h"
#include "pointer_deleter.h"
#include <vector>

namespace ipgdlib
{
    namespace op
    {

        template <typename TOutput>
        struct CAbsOperatorT :
            public IOperatorT<TOutput>
        {
            
            using ret_type = TOutput;

            ~CAbsOperatorT()
            {
                for (auto i : this->m_vInput)
                    i.execute();
            }

            CAbsOperatorT(std::initializer_list<pointer_deleter<IOperator>> operands) :
                m_vInput(std::move(operands))
            {
            }

            void reset() noexcept override
            {
                for (auto& i : this->m_vInput)
                    i->reset();
            }

            size_t getOperatorInputCount()
            {
                return this->m_vInput.size();
            }

        protected:
            IOperator* getOperatorInput(size_t index) const
            {
                return this->m_vInput[index];
            }

            std::vector<pointer_deleter<IOperator>>& getInputVector() noexcept
            {
                return this->m_vInput;
            }

        private:
            std::vector<pointer_deleter<IOperator>> m_vInput;
        };

    }
}


