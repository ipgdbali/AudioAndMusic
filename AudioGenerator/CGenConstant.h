#pragma once

#include "CAbsStreamProducerT.h"

namespace ipgdlib
{
	namespace stream
	{

		template <typename T>
		struct CGenConstant :
			public CAbsStreamProducerT<T>
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

		private:
			T m_Constant;
		};

	}

};

