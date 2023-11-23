#pragma once

#include "IOperator.h"

namespace ipgdlib
{
	namespace processor
	{

		template <typename T>
		struct IOperatorT :
			virtual public IOperator
		{
			virtual T get() noexcept = 0;

			eTypeKind getTypeKind() const noexcept final
			{
				return type_kind_trait<T>::typeKind();
			}

			size_t getTypeSize() const noexcept final
			{
				return type_kind_trait<T>::typeSize();
			}

		private:

			// Please check whether line below works. 
			using IOperator::as;

		};

	}
}

