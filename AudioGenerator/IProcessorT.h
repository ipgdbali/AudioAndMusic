#pragma once

#include "IProcessor.h"

namespace ipgdlib
{
	namespace processor
	{

		template <typename T>
		struct IProcessorT :
			public IProcessor
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

