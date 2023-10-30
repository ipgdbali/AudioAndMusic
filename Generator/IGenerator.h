#pragma once

#include "ITypeKind.hpp"

namespace ipgdlib
{
	struct IGenerator :
		public ITypeKind
	{
		virtual void reset() noexcept = 0;
	};

	template <typename T>
	struct IGeneratorT :
		public IGenerator
	{
		virtual T get() noexcept = 0;
	};

	template <typename T>
	struct CAbsGenerator :
		public IGeneratorT<T>
	{
		using type = T;

		CAbsGenerator() :
			m_TypeKind<T>()
		{
		}

		size_t getTypeSize() const noexcept final
		{
			return this->m_TypeKind.getTypeSize();
		}

		eTypeKind getTypeKind() const noexcept final
		{
			return this->m_TypeKind.getTypeKind();
		}

	private:
		CTypeKind m_TypeKind;
	};

}