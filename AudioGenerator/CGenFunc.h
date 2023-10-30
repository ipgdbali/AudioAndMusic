#pragma once

#include "CAbsStreamProducerT.h"
#include "eFloatingPointKind.h"
#include "wrap_param.h"

namespace ipgdlib
{
    namespace stream
    {
        #define M_PI 3.14159265358979323846
        #define M_PI2 (2 * M_PI)

        template <eFloatingPointKind fpk,eWrapParam wp = ewpPointer>
        struct CGenSine :
            public CAbsStreamProducerT<TFPKind<fpk>>
        {
            using float_type    = TFPKind<fpk>;
            using param_type    = wrap_param<IStreamProducerT< std::pair<float_type,bool> >, wp>;
            using ret_type      = float_type;

            ~CGenSine()
            {
                if constexpr (wp == ewpPointer)
                    this->m_Source.execute();
            }

            CGenSine(param_type::type genFrequency) :
                m_Source(param_type::transfer(genFrequency))
            {
            }

            void reset() noexcept final
            {
                param_type::dereference(this->m_Source).reset();
            }

            ret_type get() noexcept final
            {
                if constexpr (fpk == efpk32Bit)
                    return sinf(param_type::dereference(this->m_Source).get().first * M_PI2);
                else
                    return sin(param_type::dereference(this->m_Source).get().first * M_PI2);
            }

        private:
            param_type::type m_Source;
            
        };

        template <eFloatingPointKind fpk, eWrapParam wp = ewpPointer>
        struct CGenPWM :
            public CAbsStreamProducerT<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using param_freq_type = typename wrap_param<IStreamProducerT<std::pair<float_type, bool>>, wp>;
            using param_dutycycle_type = typename wrap_param<IStreamProducerT<float_type>, wp>;

            ~CGenPWM()
            {
                if constexpr (wp == ewpPointer)
                {
                    this->m_Source.execute();
                    this->m_DutyCycle.execute();
                }
            }

            CGenPWM(param_freq_type::type genFrequency,param_dutycycle_type::type genDutyCycle) :
                m_Source(param_freq_type::transfer(genFrequency)),m_DutyCycle(param_dutycycle_type::transfer(genDutyCycle))
            {
            }

            void reset() noexcept final
            {
                param_freq_type::dereference(this->m_Source).reset();
                param_dutycycle_type::dereference(this->m_DutyCycle).reset();
            }

            float_type get() noexcept final
            {
                static float_type dutyCycle;

                this->m_vSource = param_freq_type::dereference(this->m_Source).get();
                if (this->m_vSource.second)
                    dutyCycle = param_dutycycle_type::dereference(this->m_DutyCycle).get();

                if (this->m_vSource.first < dutyCycle)
                    return 1.0;
                else
                    return -1.0;
            }

        private:
            std::pair<float_type, bool> m_vSource;
            param_freq_type::type       m_Source;
            param_dutycycle_type::type  m_DutyCycle;

        };

        template <eFloatingPointKind fpk, eWrapParam wp = ewpPointer>
        struct CGenTriangle :
            public CAbsStreamProducerT<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;
            using param_type = typename wrap_param<IStreamProducerT<float_type>, wp>;

            ~CGenTriangle()
            {
                if constexpr (wp == ewpPointer)
                {
                    this->m_Source.execute();
                    this->m_DutyCycle.execute();
                }
            }

            CGenTriangle(param_type::type genFrequency, param_type::type genDutyCycle) :
                m_Source(param_type::transfer(genFrequency)), m_DutyCycle(param_type::transfer(genDutyCycle))
            {
            }

            void reset() noexcept final
            {
                param_type::dereference(this->m_Source).reset();
                param_type::dereference(this->m_DutyCycle).reset();
            }

            float_type get() noexcept final
            {
                if (param_type::dereference(this->m_Source).get() < param_type::dereference(this->m_DutyCycle).get())
                    return 1.0;
                else
                    return -1.0;
            }

        private:
            param_type::type m_Source;
            param_type::type m_DutyCycle;

        };
    }
}


