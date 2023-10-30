#pragma once

#include "wrap_param.h"
#include "CAbsStreamProducerT.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{
	namespace stream
	{

		template <typename T, eWrapParam wp = ewpPointer>
		struct CDuplicator :
			public CAbsStreamProducerT<T>
		{
			using type = T;
			using param_type = typename wrap_param<IStreamProducerT<T>, wp>;

			~CDuplicator()
			{
				if constexpr (wp == ewpPointer)
					this->m_Source.execute();
			}

			CDuplicator(size_t repeatCount, typename param_type::type source) :
				m_RepeatCount(repeatCount),m_Count(0),m_Source(param_type::transfer(source))
			{
			}

			void reset() noexcept final
			{
				param_type::dereference(this->m_Source).reset();
			}

			T get() noexcept final
			{
				if (m_Count == 0)
					this->m_Value = param_type::dereference(this->m_Source).get();
				this->m_Count++;
				if (m_Count == this->m_RepeatCount)
					m_Count = 0;
				return this->m_Value;
			}

		private:
			T							m_Value;
			size_t						m_RepeatCount;
			size_t						m_Count;
			param_type::type			m_Source;
		};

	}
}

