#pragma once

#include "CAbsProducer.h"
#include "pointer_deleter.h"
#include <vector>

namespace ipgdlib
{
    namespace processor
    {

        class CAbsProducerVector :
            public CAbsProducer
        {

        public:
            ~CAbsProducerVector()
            {
                for (auto i : this->m_Operators)
                    i.destroy();
            }

            CAbsProducerVector(std::vector<pointer_deleter<CAbsOperatorProducer>> op) :
                m_Operators(std::move(op)),
                m_CheckOpGetCount(0),
                m_CheckOpGet(m_Operators.size()),
                m_CheckOpResetCount(0),
                m_CheckOpReset(m_Operators.size())
            {

                for (size_t li = 0; li < this->m_Operators.size(); li++)
                    this->setChildIndex(this->m_Operators[li], li);

                for (size_t li = 0; li < this->getOperatorCount(); li++)
                    this->m_CheckOpGet[li] = false;

                for (size_t li = 0; li < this->getOperatorCount(); li++)
                    this->m_CheckOpReset[li] = false;

            }

            size_t getOperatorCount() const noexcept final
            {
                return this->m_Operators.size();
            }

        protected:

            // check get automatically call next after all operator has been called. 
            // asumtion all operator must be connected. 
            void onOperatorGet(size_t index) override
            {
                if (!this->m_CheckOpGet[index])
                {
                    this->m_CheckOpGet[index] = true;
                    m_CheckOpGetCount++;
                    if (m_CheckOpGetCount == this->getOperatorCount())
                    {
                        this->next();
                        for (size_t li = 0; li < this->getOperatorCount(); li++)
                            this->m_CheckOpGet[li] = false;
                        this->m_CheckOpGetCount = 0;
                    }
                }
                else
                    throw std::runtime_error("get called more than once");
            }

            void onOperatorReset(size_t index) override
            {
                if (!this->m_CheckOpReset[index])
                {
                    this->m_CheckOpReset[index] = true;
                    m_CheckOpResetCount++;
                    if (m_CheckOpResetCount == this->getOperatorCount())
                    {
                        this->reset();
                        for (size_t li = 0; li < this->getOperatorCount(); li++)
                            this->m_CheckOpReset[li] = false;
                        this->m_CheckOpResetCount = 0;
                    }
                }
                else
                    throw std::runtime_error("get called more than 1");
            }
            
            IOperator &getOperator(size_t index) noexcept final
            {
                return *(IOperator*)this->m_Operators[index];
            }

        private:
            std::vector<pointer_deleter<CAbsOperatorProducer>> m_Operators;
            
            size_t              m_CheckOpGetCount;
            std::vector<bool>   m_CheckOpGet;

            size_t              m_CheckOpResetCount;
            std::vector<bool>   m_CheckOpReset;
        };

    }
}

