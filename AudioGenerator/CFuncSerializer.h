#pragma once

#include "CAbsOperatorT.h"
#include <vector>

namespace ipgdlib
{
	namespace op
	{

		template <typename T>
		struct CFuncSerializer :
			public CAbsOperatorT<T>
		{
			using type = T;
			using param_type = pointer_deleter<IOperatorT<T>>;

			CFuncSerializer(std::vector<param_type> sources) :
				CAbsOperatorT<T>(std::move(sources)),
				m_Sources(std::move(sources)),m_CurrIndex(m_Sources.size()-1)
			{
			}

			void reset() noexcept final
			{
				CAbsOperatorT<T>::reset();
				m_CurrIndex = m_Sources.size() - 1;
			}

			T get() noexcept final
			{
				m_CurrIndex++;
				if (m_CurrIndex == m_Sources.size())
					m_CurrIndex = 0;
				return m_Sources[m_CurrIndex]->get();
			}

		private:
			std::vector<param_type>						m_Sources;
			size_t										m_CurrIndex;
		};
	}
}

