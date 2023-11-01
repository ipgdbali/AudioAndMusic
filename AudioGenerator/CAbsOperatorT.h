#pragma once

#include "IOperator.h"
#include "IOperatorT.h"
#include "pointer_deleter.h"
#include <vector>

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        struct CAbsOperatorT :
            public IOperatorT<T>
        {
            
            using ret_type = T;

            ~CAbsOperatorT()
            {
                for (auto i : this->m_vInput)
                    i.execute();
            }

            CAbsOperatorT(std::vector<pointer_deleter<IOperator>> vInput) :
                m_vInput(std::move(vInput))
            {
            }

            void reset() noexcept
            {
                for (auto& i : this->m_vInput)
                    i->reset();
            }

            size_t getOperatorInputCount()
            {
                return this->m_vInput.size();
            }

        protected:
            IOperator* getOperatorInput(size_t index)
            {
                return this->m_vInput[index];
            }

        private:
            std::vector<pointer_deleter<IOperator>> m_vInput;
        };

    }
}


