#pragma once

#include "wrap_param.h"
#include "CAbsStreamProducerT.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{
    namespace stream
    {
        template <typename T, eWrapParam wp = ewpPointer>
        struct CModNegate :
            public CAbsStreamProducerT<T>
        {
            using param_type = typename wrap_param<IStreamProducerT<T>, wp>;

            ~CModNegate()
            {
                if constexpr (wp == ewpPointer)
                    this->m_Source.execute();
            }

            CModNegate(typename param_type::type source) :
                m_Source(param_type::transfer(source))
            {
            }

            void reset() noexcept final
            {
                param_type::dereference(this->m_Source).reset();
            }

            T get() noexcept final
            {
                return -param_type::dereference(this->m_Source).get();
            }

        private:
            param_type::type m_Source;
        };

        template <typename T, eWrapParam wp = ewpPointer>
        struct CModOffset :
            public CAbsStreamProducerT<T>
        {
            using param_type = typename wrap_param<IStreamProducerT<T>, wp>;

            ~CModOffset()
            {
                if constexpr (wp == ewpPointer)
                    this->m_Source.execute();
            }

            CModOffset(T offset,typename param_type::type source) :
                m_Source(param_type::transfer(source)),m_Offset(offset)
            {
            }

            void reset() noexcept final
            {
                param_type::dereference(this->m_Source).reset();
            }

            T get() noexcept final
            {
                return  this->m_Offset + param_type::dereference(this->m_Source).get();
            }

        private:
            param_type::type    m_Source;
            T                   m_Offset;
        };

        template <typename T, eWrapParam wp = ewpPointer>
        struct CModMul :
            public CAbsStreamProducerT<T>
        {
            using param_type = typename wrap_param<IStreamProducerT<T>, wp>;

            ~CModMul()
            {
                if constexpr (wp == ewpPointer)
                    this->m_Source.execute();
            }

            CModMul(T mul,typename param_type::type source) :
                m_Source(param_type::transfer(source)), m_Mul(mul)
            {
            }

            void reset() noexcept final
            {
                param_type::dereference(this->m_Source).reset();
            }

            T get() noexcept final
            {
                return this->m_Mul * param_type::dereference(this->m_Source).get();
            }

        private:
            param_type::type    m_Source;
            T                   m_Mul;
        };

    }
}

