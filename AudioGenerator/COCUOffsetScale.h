#pragma once

#include "CAbsOperatorCommonUnary.h"
#include "eFloatingPointKind.h"
#include "function.h"
#include <functional>

namespace ipgdlib
{

    namespace processor
    {

        template <eFloatingPointKind fpk>
        struct COCUOffsetScale :
            public CAbsOperatorCommonUnary<TFPKind<fpk>>
        {
            using float_type = TFPKind<fpk>;

            COCUOffsetScale(
                float_type offset,
                float_type scale,
                pointer_deleter<IOperatorT<float_type>> operand
            ) : COCUOffsetScale<fpk>(offset,scale,ipgdlib::function::fnLinear<float_type>,operand)
            {
            }


            COCUOffsetScale(
                float_type offset,
                float_type scale,
                std::function<float_type(float_type)> fun, 
                pointer_deleter<IOperatorT<float_type>> operand
            ) :
                m_Offset(offset), 
                m_Scale(scale),
                m_Function(fun),
                CAbsOperatorCommonUnary<float_type>(operand)
            {
            }

            float_type get() noexcept final
            {
                return this->m_Offset + this->m_Function(this->getOperand().get()) * this->m_Scale;
            }

            float_type getOffset() const noexcept
            {
                return this->m_Offset;
            }

            void setOffset(float_type offset)
            {
                this->m_Offset = offset;
            }

            float_type getScale() const noexcept
            {
                return this->m_Scale;
            }

            void setscale(float_type scale)
            {
                this->m_Scale = scale;
            }

            std::function<float_type(float_type)> getFunction() const noexcept
            {
                return this->m_Function;
            }

            void setscale(std::function<float_type(float_type)> fun)
            {
                this->m_Function = fun;
            }

        private:
            float_type                              m_Offset;
            float_type                              m_Scale;
            std::function<float_type(float_type)>   m_Function;

        };

    }
}

