#ifndef TYPEKIND_HPP
#define TYPEKIND_HPP

#include <cstddef>
#include <cstdint>

namespace ipgdlib
{
    enum eTypeKind : uint8_t {
        etkInt8,
        etkUInt8,
        etkInt16,
        etkUInt16,
        etkInt32,
        etkUInt32,
        etkInt64,
        etkUInt64,
        etkFP32,
        etkFP64,
        etkBool,
        etkOther
    };

    template <typename T>
    struct type_kind_trait
    {
        static constexpr size_t typeSize() noexcept
        {
            return sizeof(T);
        }

        static constexpr eTypeKind typeKind() noexcept
        {
            if constexpr (std::is_same<T, int8_t>::value)
                return etkInt8;
            else
                if constexpr (std::is_same<T, uint8_t>::value)
                    return etkUInt8;
                else
                    if constexpr (std::is_same<T, int16_t>::value)
                        return etkInt16;
                    else
                        if constexpr (std::is_same<T, uint16_t>::value)
                            return etkUInt16;
                        else
                            if constexpr (std::is_same<T, int32_t>::value)
                                return etkInt32;
                            else
                                if constexpr (std::is_same<T, uint32_t>::value)
                                    return etkUInt32;
                                else
                                    if constexpr (std::is_same<T, int64_t>::value)
                                        return etkInt64;
                                    else
                                        if constexpr (std::is_same<T, uint64_t>::value)
                                            return etkUInt64;
                                        else
                                            if constexpr (std::is_same<T, float>::value)
                                                return etkFP32;
                                            else
                                                if constexpr (std::is_same<T, double>::value)
                                                    return etkFP64;
                                                else
                                                    if constexpr (std::is_same<T, bool>::value)
                                                        return etkBool;
                                                    else
                                                        return etkOther;
        }
    };

    struct ITypeKind
    {
        virtual size_t getTypeSize() const noexcept = 0;
        virtual eTypeKind getTypeKind() const noexcept = 0;
    };

    template <typename T>
    struct CAbsTypeKind :
        public ITypeKind
    {
        using type = T;
        constexpr size_t getTypeSize() const noexcept override
        {
            return sizeof(T);
        }

    };

    template <typename T>
    struct CTypeKind :
        public CAbsTypeKind<T>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkOther;
        }
    };

    template <>
    struct CTypeKind<int8_t> :
        public CAbsTypeKind<int8_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept final
        {
            return etkInt8;
        }
    };

    template <>
    struct CTypeKind<uint8_t> :
        public CAbsTypeKind<uint8_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkUInt8;
        }
    };

    template <>
    struct CTypeKind<int16_t> :
        public CAbsTypeKind<int16_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkInt16;
        }
    };

    template <>
    struct CTypeKind<uint16_t> :
        public CAbsTypeKind<uint16_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkUInt16;
        }
    };

    template <>
    struct CTypeKind<int32_t> :
        public CAbsTypeKind<int32_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkInt32;
        }
    };

    template <>
    struct CTypeKind<uint32_t> :
        public CAbsTypeKind<uint32_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkUInt32;
        }
    };

    template <>
    struct CTypeKind<int64_t> :
        public CAbsTypeKind<int64_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkInt64;
        }
    };

    template <>
    struct CTypeKind<uint64_t> :
        public CAbsTypeKind<uint64_t>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkUInt64;
        }
    };

    template <>
    struct CTypeKind<float> :
        public CAbsTypeKind<float>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkFP32;
        }
    };

    template <>
    struct CTypeKind<double> :
        public CAbsTypeKind<double>
    {
        constexpr eTypeKind getTypeKind() const noexcept override
        {
            return etkFP64;
        }
    };

};

#endif