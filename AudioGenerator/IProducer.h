#pragma once
#include "IOperator.h"

namespace ipgdlib
{

	namespace processor
	{
		struct IProducer
		{
			virtual ~IProducer() {
			};

			/// <summary>
			/// Operator that this producer has
			/// </summary>
			/// <returns></returns>
			virtual size_t getOperatorCount() const noexcept = 0;
			
			/// <summary>
			/// take the operator
			/// </summary>
			/// <param name="index"></param>
			/// <returns></returns>
			virtual IOperator &getOperator(size_t index) noexcept = 0;
		};
	}

}
