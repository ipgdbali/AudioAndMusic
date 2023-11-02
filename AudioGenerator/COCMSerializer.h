#pragma once

#include "CAbsOperatorCommon.h"
#include <vector>
#include <initializer_list>

namespace ipgdlib
{
	namespace op
	{

		template <typename T>
		struct COCMSerializer :
			public CAbsOperatorCommon<T>
		{
			using type = T;
			using param_type = pointer_deleter<IOperatorT<T>>;

			COCMSerializer(std::initializer_list<param_type> sources) :
				CAbsOperatorCommon<T>(sources),
				m_CurrIndex(sources.size() - 1)
			{
			}

			COCMSerializer(std::vector<param_type> sources) :
				CAbsOperatorCommonUnary<T>(sources),
				m_CurrIndex(sources.size()-1)
			{
			}

			void reset() noexcept final
			{
				CAbsOperatorCommonUnary<T>::reset();
				m_CurrIndex = this->getOperandCount() - 1;
			}

			T get() noexcept final
			{
				m_CurrIndex++;
				if (m_CurrIndex == this->getOperandCount())
					m_CurrIndex = 0;
				return this->getOperand(m_CurrIndex)->get();
			}

		private:
			size_t										m_CurrIndex;
		};
	}
}

