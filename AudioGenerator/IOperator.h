#pragma once

#include "type_kind.h"

namespace ipgdlib
{
	namespace processor
	{

		template <typename T>
		struct IOperatorT;

		struct IOperator :
			public ITypeKind
		{
			virtual ~IOperator() {};

			virtual void reset() noexcept = 0;
			
			template <typename T>
			IOperatorT<T> &as()
			{
				return dynamic_cast<IOperatorT<T>&>(*this);
			}

			virtual size_t getOperandCount() const noexcept = 0;
		};

	}

}

