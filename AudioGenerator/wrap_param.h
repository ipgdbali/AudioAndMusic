#pragma once

#include <memory>
#include "pointer_deleter.h"

namespace ipgdlib
{
	enum eWrapParam { 
		ewpLeftReference, 
		ewpPointer
	};

	template <typename T,eWrapParam e>
	struct wrap_param	{
	};

	template <typename T>
	struct wrap_param<T, ewpPointer> {

		using type = pointer_deleter<T>;

		static type && transfer(type & obj)
		{
			return std::move(obj);
		}

		static T& dereference(type& obj)
		{
			return *(obj);
		}
	};
}


