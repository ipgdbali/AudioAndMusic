#pragma once

#include "CAbsOperatorT.h"
#include <initializer_list>

namespace ipgdlib
{
    namespace op
    {

        template <typename TIO>
        class CAbsOperatorCommonMultinaryT :
            public CAbsOperatorT<TIO>
        {
            using param_type = pointer_deleter<IOperatorT<TIO>>;

            CAbsOperatorCommonMultinaryT(
                std::initializer_list<param_type operands) :
                CAbsOperatorT<TIO>(operands)
            {
            }

        };

    }
}


