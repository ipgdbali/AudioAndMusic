#ifndef RETURN_WRAPPER_HPP
#define RETURN_WRAPPER_HPP

#include <memory>

namespace ipgdlib
{

    enum eWrapReturn { ewrNoChange, ewrPointer, ewrReference, ewrUniquePtr, ewrSharedPtr, ewrWeakPtr };

    template <typename T, eWrapReturn e>
    struct wrap_ret {
    };

    template <typename T>
    struct wrap_ret<T, ewrNoChange> {
        using type = T;
        using type_const = const T;
    };

    template <typename T>
    struct wrap_ret<T, ewrPointer> {
        using type = T*;
        using type_const = T const*;
    };


    template <typename T>
    struct wrap_ret<T, ewrReference> {
        using type = T&;
        using type_const = T const&;
    };


    template <typename T>
    struct wrap_ret<T, ewrUniquePtr> {
        using type = std::unique_ptr<T>;
        using type_const = std::unique_ptr<T const>;
    };

    template <typename T>
    struct wrap_ret<T, ewrSharedPtr> {
        using type = std::shared_ptr<T>;
        using type_const = std::shared_ptr<T const>;
    };

    template <typename T>
    struct wrap_ret<T, ewrWeakPtr> {
        using type = std::weak_ptr<T>;
        using type_const = std::weak_ptr<T const>;
    };

    template <typename T, bool bConst, eWrapReturn e>
    struct wrap_ret_constness {
    private:
        using TWrap = wrap_ret<T, e>;
    public:
        using type = typename std::conditional<bConst, typename TWrap::type_const, typename TWrap::type>::type;
    };

};

#endif