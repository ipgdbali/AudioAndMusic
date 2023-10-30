#pragma once

#include <stdexcept>
#include <iostream>

namespace ipgdlib
{

	template <typename T>
	struct pointer_deleter
	{
		void execute()
		{
			if (this->m_Pointer != nullptr && this->m_bDeleted == true)
			{
				delete this->m_Pointer;
				this->m_Pointer = nullptr;
				this->m_bDeleted = false;
			}
		}

		pointer_deleter(const pointer_deleter<T>& ref) :
			m_Pointer(ref.m_Pointer),m_bDeleted(ref.m_bDeleted)
		{
		}

		void operator = (const pointer_deleter<T>& ref) = delete;

		pointer_deleter(pointer_deleter<T>&& ref) :
			m_Pointer(ref.m_Pointer), m_bDeleted(ref.m_bDeleted)
		{
			ref.m_Pointer = nullptr;
			ref.m_bDeleted = false;
		}

		void operator = (pointer_deleter<T>&& ref) = delete;

		pointer_deleter(T* ptr, bool bDeleted = true) :
			m_Pointer(ptr), m_bDeleted(bDeleted)
		{
		}

		T* operator->()
		{
			return this->m_Pointer;
		}

		T &operator *() const
		{
			return *this->m_Pointer;
		}

	private:
		T*		m_Pointer;
		bool	m_bDeleted;
	};

}


