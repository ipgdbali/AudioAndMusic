#pragma once

#include <utility>
#include "CAbsOperatorUnaryT.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace op
    {

        template <eFloatingPointKind fpk>
        struct COscillator :
            public CAbsOperatorT<TFPKind<fpk>>
        {
            using T = TFPKind<fpk>;
            using param_type = pointer_deleter<IOperatorT<TFPKind<fpk>>>;

            COscillator(size_t sampleRate,param_type freq) :
                CAbsOperatorT<T>({freq.as<IOperator>()}),
                m_SampleRate(sampleRate), 
                m_Phase(0),m_bNewPhase(true),
                m_Freq(freq)
            {
            }

            size_t getSampleRate() const noexcept
            {
                return this->m_SampleRate;
            }

            void reset() noexcept final
            {
                CAbsOperatorT<T>::reset();
                this->m_Phase = 0;
                this->m_bNewPhase = true;
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
            bool            m_bNewPhase;
            size_t          m_SampleRate;
            IOperatorT<TFPKind<fpk>>* m_Freq;
        };

    }

}


