#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{
    namespace op
    {

        template <eFloatingPointKind fpk>
        struct COCUCosine :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using ret_type = float_type;

            COCUCosine(pointer_deleter<IOperatorT<float_type>> opOsc) :
                CAbsOperatorCommonUnary<float_type>({ opOsc.as<IOperator>() }),
                m_Source(opOsc)
            {
            }

            ret_type get() noexcept final
            {
                if constexpr (fpk == efpk32Bit)
                    return sinf(this->m_Source->get());
                else
                    return sin(this->m_Source->get());
            }

        private:
            IOperatorT<float_type>* m_Source;

        };

    }
}

