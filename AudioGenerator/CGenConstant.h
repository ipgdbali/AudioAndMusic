#pragma once

#include "CAbsOperatorGenerator.h"

namespace ipgdlib
{
	namespace processor
	{

		template <typename T>
		struct CGenConstant :
			public CAbsOperatorGenerator<T>
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

