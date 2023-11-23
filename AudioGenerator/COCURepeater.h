#pragma once

#include "CAbsOperatorCommonUnary.h"

namespace ipgdlib
{
	namespace processor
	{

		template <typename TIO>
		struct COCURepeater :
			public CAbsOperatorCommonUnary<TIO>
		{
			using type = TIO;
			using param_type = pointer_deleter<IOperatorT<TIO>>;

			COCURepeater(size_t repeatCount, param_type source) :
				CAbsOperatorCommonUnary<TIO>(source),
				m_RepeatCount(repeatCount),m_Count(0)
			{
			}

			TIO get() noexcept final
			{
				if (m_Count == 0)
					this->m_Value = this->getOperand().get();
				this->m_Count++;
				if (m_Count == this->m_RepeatCount)
					m_Count = 0;
				return this->m_Value;
			}

		private:
			TIO							m_Value;
			size_t						m_RepeatCount;
			size_t						m_Count;
		};

	}
}

