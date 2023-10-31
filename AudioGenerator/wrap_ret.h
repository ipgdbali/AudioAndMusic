#ifndef RETURN_WRAPPER_HPP
#define RETURN_WRAPPER_HPP

#include <memory>

namespace ipgdlib
{

    enum eWrapReturn { 
        ewrPointer, 
    };

    template <typename T, eWrapReturn e>
    struct wrap_ret {
    };

    template <typename T>
    struct wrap_ret<T, ewrPointer> {
        using type = T*;
        using type_const = T const*;
    };

};

#endif