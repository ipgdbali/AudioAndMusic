#pragma once

#include "CAbsOperatorT.h"
#include "pointer_deleter.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{
	namespace op
	{

		template <typename T>
		struct CFuncFork :
			public CAbsOperatorT<T>
		{
			using type = T;
			using param_type = pointer_deleter<IOperatorT<T>>;

			CFuncFork(size_t repeatCount, param_type source) :
				CAbsOperatorT<T>({source.as<IOperator>()}),
				m_RepeatCount(repeatCount),m_Count(0),m_Source(source)
			{
			}

			T get() noexcept final
			{
				if (m_Count == 0)
					this->m_Value = this->m_Source->get();
				this->m_Count++;
				if (m_Count == this->m_RepeatCount)
					m_Count = 0;
				return this->m_Value;
			}

		private:
			T							m_Value;
			size_t						m_RepeatCount;
			size_t						m_Count;
			IOperatorT<T>*				m_Source;
		};

	}
}

