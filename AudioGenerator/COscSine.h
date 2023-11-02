#pragma once

#include "CAbsOperatorT.h"
#include "IOperatorT.h"
#include "eFloatingPointKind.h"
#include "pointer_deleter.h"
#include <utility>

namespace ipgdlib
{
    namespace op
    {

        template <eFloatingPointKind fpk>
        struct COscSine :
            public CAbsOperatorT<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using ret_type = float_type;

            COscSine(pointer_deleter<IOperatorT<float_type>> opOsc) :
                CAbsOperatorT<float_type>({ opOsc.as<IOperator>() }),
                m_Source(opOsc)
            {
            }

            ret_type get() noexcept final
            {
                if constexpr (fpk == efpk32Bit)
                    return sinf(this->m_Source->get() * 3.14159265358979323846 * 2);
                else
                    return sin(this->m_Source->get() * 3.14159265358979323846 * 2);
            }

        private:
            IOperatorT<float_type> *m_Source;

        };

    }
}

