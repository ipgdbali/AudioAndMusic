#pragma once

#include "wrap_param.h"
#include "CAbsStreamProducerT.h"
#include <vector>

namespace ipgdlib
{
	namespace stream
	{

		template <typename T, eWrapParam wp = ewpPointer>
		struct CFuncSerialize :
			public CAbsStreamProducerT<T>
		{
			using type = T;
			using param_type = typename wrap_param<IStreamProducerT<T>, wp>;

			~CFuncSerialize()
			{
				if constexpr (wp == ewpPointer)
					for(auto & item : this->m_Sources)
							item.execute();
			}

			CFuncSerialize(std::vector<typename param_type::type> sources) :
				m_Sources(std::move(sources)),m_CurrIndex(m_Sources.size()-1)
			{
			}

			void reset() noexcept final
			{
				for (auto& source : m_Sources)
					param_type::dereference(source).reset();
				m_CurrIndex = m_Sources.size() - 1;
			}

			T get() noexcept final
			{
				m_CurrIndex++;
				if (m_CurrIndex == m_Sources.size())
					m_CurrIndex = 0;
				return param_type::dereference(m_Sources[m_CurrIndex]).get();
			}

		private:
			std::vector<typename param_type::type>	m_Sources;
			size_t										m_CurrIndex;
		};
	}
}

