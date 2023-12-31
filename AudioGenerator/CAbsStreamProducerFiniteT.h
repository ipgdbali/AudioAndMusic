#pragma once

#include "IStreamProducerFiniteT.h"
#include "type_kind_trait.h"

namespace ipgdlib
{
    namespace stream
    {

        template <typename T>
        class CAbsStreamProducerFiniteT :
            public IStreamProducerFiniteT<T>
        {
            constexpr size_t getTypeSize() const noexcept final
            {
                return sizeof(T);
            }

            constexpr eTypeKind getTypeKind() const noexcept final
            {
                return type_kind_trait<T>::getTypeKind();
            }

        };

    }
}


