#pragma once

#include "CAbsProcessorT.h"

namespace ipgdlib
{
    namespace processor
    {

        template <typename T>
        struct CAbsOpBinaryT :
            public CAbsProcessorT<T>
        {

            CAbsOpBinaryT(pointer_deleter<IProcessorT<T>> left, pointer_deleter<IProcessorT<T>> right) :
                CAbsProcessorT<T>({ left.as<IProcessor>() , right.as<IProcessor>() }),
                m_Left(left), m_Right(right)
            {
            }

            void reset() noexcept override
            {
                this->m_Left->reset();
                this->m_Right->reset();
            }

        protected:
            IProcessorT<T>* getLeft() const noexcept
            {
                return this->m_Left;
            }

            IProcessorT<T>* getRight() const noexcept
            {
                return this->m_Right;
            }

        private:
            IProcessorT<T>* m_Left;
            IProcessorT<T>* m_Right;
        };

    }
}

