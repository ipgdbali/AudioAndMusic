#pragma once

#include "IProcessor.h"
#include "IProcessorT.h"
#include "pointer_deleter.h"
#include <vector>

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct CAbsProcessorT :
            public IProcessorT<T>
        {
            ~CAbsProcessorT()
            {
                for (auto i : this->m_vInput)
                    i.execute();
            }

            CAbsProcessorT(std::vector<pointer_deleter<IProcessor>> vInput) :
                m_vInput(std::move(vInput))
            {
            }

            size_t getProcessorInputCount()
            {
                return this->m_vInput.size();
            }

        protected:
            IProcessor* getProcessorInput(size_t index)
            {
                return this->m_vInput[index];
            }

        private:
            std::vector<pointer_deleter<IProcessor>> m_vInput;
        };

    }
}


