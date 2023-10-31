#pragma once

#include <utility>
#include "CAbsStreamProducerT.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{

    namespace stream
    {

        template <eFloatingPointKind fpk>
        struct CGenFPFrequency :
            public CAbsStreamProducerT<std::pair<TFPKind<fpk>,bool>>
        {
            using float_type    = typename TFPKind<fpk>;
            using param_type    = typename wrap_param<IStreamProducerT<float_type>, wp>;
            using ret_type      = std::pair<TFPKind<fpk>, bool>;

            CGenFPFrequency(size_t sampleRate,param_type::type freq) :
                m_Phase(0),m_Source(param_type::transfer(freq)),m_SampleRate(sampleRate),m_bNewPhase(true)
            {
            }

            size_t getSampleRate() const noexcept
            {
                return this->m_SampleRate;
            }

            void reset() noexcept final
            {
                param_type::dereference(this->m_Source).reset();
                this->m_Phase = 0;
                this->m_bNewPhase = true;
            }

            ret_type get() noexcept final 
            {
                ret_type ret(this->m_Phase, this->m_bNewPhase);

                auto freq = param_type::dereference(this->m_Source).get();

                this->m_Phase += (freq / this->m_SampleRate);
                if (this->m_bNewPhase)
                    this->m_bNewPhase = false;
                if (this->m_Phase >= 1.0)
                {
                    this->m_Phase = this->m_Phase - (int)this->m_Phase;
                    this->m_bNewPhase = true;
                }

                return ret;
            }

        private:

            float_type          m_Phase;
            bool                m_bNewPhase;
            size_t              m_SampleRate;
            param_type::type    m_Source;

        };

    }

}


