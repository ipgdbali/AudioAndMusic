#pragma once

#include "CAbsOperatorCommonUnary.h"

namespace ipgdlib
{
	namespace op
	{

		template <typename TIO>
		struct COCURepeater :
			public CAbsOperatorCommonUnary<TIO>
		{
			using type = T;
			using param_type = pointer_deleter<IOperatorT<TIO>>;

			COCURepeater(size_t repeatCount, param_type source) :
				CAbsOperatorCommonUnary<TIO>({source.as<IOperator>()}),
				m_RepeatCount(repeatCount),m_Count(0)
			{
			}

			T get() noexcept final
			{
				if (m_Count == 0)
					this->m_Value = this->getOperand(0)->get();
				this->m_Count++;
				if (m_Count == this->m_RepeatCount)
					m_Count = 0;
				return this->m_Value;
			}

		private:
			T							m_Value;
			size_t						m_RepeatCount;
			size_t						m_Count;
		};

	}
}

