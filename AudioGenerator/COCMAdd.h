#pragma once

#include "CAbsOperatorCommon.h"
#include <vector>
#include <initializer_list>
#include <numeric>

namespace ipgdlib
{
	namespace processor
	{

		template <typename TIO>
		struct COCMAdd :
			public CAbsOperatorCommon<TIO>
		{
			using type = TIO;
			using param_type = pointer_deleter<IOperatorT<TIO>>;

			COCMAdd(std::initializer_list<param_type> sources) :
				CAbsOperatorCommon<TIO>(sources)
			{
			}

			COCMAdd(std::vector<param_type> sources) :
				CAbsOperatorCommon<TIO>(sources)
			{
			}

			void reset() noexcept final
			{
				CAbsOperatorCommon<TIO>::reset();
			}

			TIO get() noexcept final
			{
				TIO ret = 
				std::accumulate(
					this->m_vOperands.cbegin(),
					this->m_vOperands.cend(),
					(TIO)0.0, [](TIO a, pointer_deleter<IOperator> b) {
						return a + b.as<IOperatorT<TIO>>()->get();
					}
				);

				return ret;
			}
		};
	}
}

