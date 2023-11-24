#pragma once

#include <cstdio>
#include <utility>
#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COscFreq :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using T = TFPKind<fpk>;
            using param_type = pointer_deleter<IOperatorT<T>>;

            COscFreq(size_t sampleRate,param_type freq) :
                CAbsOperatorCommonUnary<T>(freq),
                m_SampleRate(sampleRate), 
                m_Phase(0),m_Freq(freq)
            {
            }

            size_t getSampleRate() const noexcept
            {
                return this->m_SampleRate;
            }

            void reset() noexcept final
            {
                CAbsOperatorCommonUnary<T>::reset();
                this->m_Phase = 0;
            }

            T get() noexcept final 
            {
                T ret(this->m_Phase);

                this->m_Phase += (this->m_Freq->get() / this->m_SampleRate);
                if (this->m_Phase >= 1.0)
                    this->m_Phase = this->m_Phase - (int)this->m_Phase;

                return ret;
            }

        private:

            TFPKind<fpk>    m_Phase;
            size_t          m_SampleRate;
            IOperatorT<TFPKind<fpk>>* m_Freq;
        };

    }

}


