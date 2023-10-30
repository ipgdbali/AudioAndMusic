#pragma once

#include "IStreamProducerT.h"
#include "type_kind.h"

namespace ipgdlib
{
	namespace stream
	{

		template <typename T>
		struct CAbsStreamProducerT :
			public IStreamProducerT<T>
		{

			constexpr size_t getTypeSize() const noexcept final
			{
				return sizeof(T);
			}

			constexpr eTypeKind getTypeKind() const noexcept final
			{
				return type_kind<T>::getTypeKind();
			}

		};

	}

}


