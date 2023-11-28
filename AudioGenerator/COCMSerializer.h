#pragma once

#include "CAbsOperatorCommon.h"
#include <vector>
#include <initializer_list>

namespace ipgdlib
{
	namespace processor
	{

		template <typename TIO>
		struct COCMSerializer :
			public CAbsOperatorCommon<TIO>
		{
			using type = TIO;
			using param_type = pointer_deleter<IOperatorT<TIO>>;

			COCMSerializer(std::initializer_list<param_type> sources) :
				CAbsOperatorCommon<TIO>(sources),
				m_CurrIndex(sources.size() - 1)
			{
			}

			COCMSerializer(std::vector<param_type> sources) :
				CAbsOperatorCommon<TIO>(sources),
				m_CurrIndex(sources.size()-1)
			{
			}

			void reset() noexcept final
			{
				CAbsOperatorCommon<TIO>::reset();
				m_CurrIndex = this->getOperandCount() - 1;
			}

			TIO get() noexcept final
			{
				m_CurrIndex++;
				if (m_CurrIndex == this->getOperandCount())
					m_CurrIndex = 0;
				return this->getOperand(m_CurrIndex).get();
			}

		private:
			size_t	m_CurrIndex;
		};
	}
}

