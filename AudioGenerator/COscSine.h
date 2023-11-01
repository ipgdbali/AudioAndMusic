#pragma once

#include "CAbsOperatorT.h"
#include "IOperatorT.h"
#include "eFloatingPointKind.h"
#include "pointer_deleter.h"
#include <utility>

#define M_PI 3.14159265358979323846
#define M_PI2 (2 * M_PI)

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

            COscSine(pointer_deleter<IOperatorT<std::pair<float_type, bool>>> opOsc) :
                CAbsOperatorT<float_type>({ opOsc.as<IOperator>() }),
                m_Source(opOsc)
            {
            }

            ret_type get() noexcept final
            {
                if constexpr (fpk == efpk32Bit)
                    return sinf(this->m_Source->get().first * M_PI2);
                else
                    return sin(this->m_Source->get().first * M_PI2);
            }

        private:
            IOperatorT<std::pair<float_type,bool>> *m_Source;

        };

    }
}

