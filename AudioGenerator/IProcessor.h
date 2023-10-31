#pragma once

#include "type_kind.h"

namespace ipgdlib
{
	namespace processor
	{

		template <typename T>
		struct IProcessorT;

		struct IProcessor :
			public ITypeKind
		{
			virtual ~IProcessor() {};

			virtual void reset() noexcept = 0;
			
			template <typename T>
			IProcessorT<T>* as()
			{
				return dynamic_cast<IProcessorT<T>*>(this);
			}

			virtual size_t getProcessorInputCount() = 0;
		};

	}

}

