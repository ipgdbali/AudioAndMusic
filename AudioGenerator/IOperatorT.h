#pragma once

#include "IOperator.h"

namespace ipgdlib
{
	namespace op
	{

		template <typename T>
		struct IOperatorT :
			public IOperator
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

		};

	}
}

