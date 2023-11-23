#pragma once

#include "IProducer.h"
#include "IOperatorT.h"
#include "IOperatorProducer.h"

namespace ipgdlib
{
	namespace processor
	{
		/// <summary>
		/// *Note
        /// Every get should not be called more than once.
        /// Every operator must be connected into aanother operator.
		/// </summary>
		struct CAbsProducer :
			public IProducer
		{

            struct CAbsOperatorProducer :
                virtual public IOperatorProducer
            {
                CAbsOperatorProducer(CAbsProducer* pProducer) :
                    m_Producer(pProducer),m_Index(0)
                {
                }

                CAbsProducer& getProducer() noexcept
                {
                    return *this->m_Producer;
                }

                size_t getIndex() const noexcept
                {
                    return this->m_Index;
                }

                void reset() noexcept override
                {
                    this->m_Producer->onOperatorReset(this->m_Index);
                }

            protected:
                void setIndex(size_t index)
                {
                    this->m_Index = index;
                }

                friend CAbsProducer;
            
            private:
                CAbsProducer* m_Producer;
                size_t m_Index;
            };

            template <typename T>
            struct COperatorProducerT :
                public CAbsOperatorProducer,
                public IOperatorT<T>
            {
                COperatorProducerT(CAbsProducer* pProducer,const T& obj) :
                    CAbsOperatorProducer(pProducer),m_Obj(obj)
                {
                }

                T get() noexcept override
                {
                    this->m_Producer->onOperatorGet(this->m_Index);
                    return this->m_Obj;
                }

            private:
                const T& m_Obj;
            };

        protected:

            // called by CAbsProducer::CAbsOperatorProducer
            virtual void reset() = 0;
            virtual void next() = 0;
            virtual void onOperatorGet(size_t index) = 0;
            virtual void onOperatorReset(size_t index) = 0;

            void setChildIndex(CAbsOperatorProducer *pOpProducer,size_t index)
            {
                pOpProducer->setIndex(index);
            }

		};
	}
}

