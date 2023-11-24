#pragma once

#include "CAbsOperatorGenerator.h"
#include <vector>

namespace ipgdlib
{
	namespace processor
	{

		template <typename T>
		struct CGenFiniteConstant :
			public CAbsOperatorGenerator<T>
		{

			using type = std::vector< std::pair<size_t, T> >;

			CGenFiniteConstant(type constant) :
				m_Constant(std::move(constant))
			{
				this->reset();
			}

			void reset() noexcept final
			{
				this->m_Index = 0;
				this->m_Position = 0;
				this->m_Length = this->m_Constant[this->m_Index].first;
				this->m_Value = this->m_Constant[this->m_Index].second;
			}

			T get() noexcept final
			{
				T ret = this->m_Value;
				this->m_Position++;
				if (this->m_Position == this->m_Length)
				{
					this->m_Position = 0;
					if (this->m_Index < this->m_Constant.size() - 1)
						this->m_Index++;
					else
						this->m_Index = 0;
					this->m_Length = this->m_Constant[this->m_Index].first;
					this->m_Value = this->m_Constant[this->m_Index].second;
				}
				return ret;
			}

			void setConstant(type val) noexcept
			{
				this->m_Constant = std::move(val);
			}

			const type &getConstant() const noexcept
			{
				return this->m_Constant;
			}

		private:
			type										m_Constant;

			size_t										m_Position;
			size_t										m_Length;
			size_t										m_Index;
			T											m_Value;
		};

	}

};

