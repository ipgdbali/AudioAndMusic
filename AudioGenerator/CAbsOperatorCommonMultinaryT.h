#pragma once

#include "CAbsOperatorT.h"
#include <initializer_list>

namespace ipgdlib
{
    namespace op
    {

        template <typename T>
        class CAbsOperatorCommonMultinaryT :
            public CAbsOperatorT<T>
        {
            using param_type = pointer_deleter<IOperatorT<T>>;

            CAbsOperatorCommonMultinaryT(
                std::initializer_list<pointer_deleter<IOperatorT<T>>> operands) :
                CAbsOperatorT<T>({ left.as<IOperator>() , right.as<IOperator>() }),
                m_Left(left), m_Right(right)
            {
            }

        };

    }
}


