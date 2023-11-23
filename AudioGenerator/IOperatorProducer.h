#pragma once

#include "IOperator.h"
#include "IProducer.h"

namespace ipgdlib
{
    namespace processor
    {

        struct IOperatorProducer :
            virtual public IOperator
        {
            size_t getOperandCount() const noexcept final
            {
                return 0;
            }

            virtual IProducer& getProducer() noexcept = 0;
            virtual size_t getIndex() const noexcept = 0;
        };

    }
}


