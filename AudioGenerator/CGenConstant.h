#pragma once

#include "CAbsOperatorNoInputT.h"

namespace ipgdlib
{
	namespace op
	{

		template <typename T>
		struct CGenConstant :
			public CAbsOperatorNoInputT<T>
		{
			CGenConstant(T constant) :
				m_Constant(constant)
			{
			}

			void reset() noexcept final
			{
			}

			T get() noexcept final
			{
				return m_Constant;
			}

			void setConstant(T val) noexcept
			{
				this->m_Constant = val;
			}

			T getConstant() const noexcept
			{
				return this->m_Constant;
			}

		private:
			T m_Constant;
		};

	}

};

