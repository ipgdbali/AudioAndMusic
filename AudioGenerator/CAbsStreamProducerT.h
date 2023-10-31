#pragma once

#include "IStreamProducerT.h"
#include "type_kind_trait.h"
#include "wrap_param.h"
#include <vector>

namespace ipgdlib
{
	namespace stream
	{

		template <typename T>
		struct CAbsStreamProducerT :
			public IStreamProducerT<T>
		{
			using param_type = wrap_param<IStreamProducer, wp>;

			~CAbsStreamProducerT()
			{
				if constexpr (wp == ewpPointer)
					for (auto i : this->m_vInputs)
						i.execute();
			}

			CAbsStreamProducerT(std::vector<typename param_type::type> vInput) :
				m_vInputs(std::move(vInput))
			{
			}

			size_t getInputCount() const noexcept final
			{
				return this->m_vInputs.size();
			}

			constexpr size_t getTypeSize() const noexcept final
			{
				return sizeof(T);
			}

			constexpr eTypeKind getTypeKind() const noexcept final
			{
				return type_kind_trait<T>::getTypeKind();
			}

		protected:
			param_type::type &getInput(size_t index) const
			{
				return this->m_vInputs[index];
			}

		private:
			std::vector<typename param_type::type> m_vInputs;

		};

	}

}


