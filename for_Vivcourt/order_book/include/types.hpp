#ifndef _VIVCOURT_TYPES_H_
#define _VIVCOURT_TYPES_H_

#include "common.hpp"
#include <cstdint>
#include <type_traits>
#include <string_view>

namespace vivcourt::types
{
#pragma pack(push, 1)

    template <bool Signed, uint8_t Size>
    class Numeric
    {
    public:
        ALWAYS_INLINE auto Value() const
        {
            if constexpr (Signed && (Size == 1))
            {
                return As<int8_t>();
            }
            else if constexpr (!Signed && (Size == 1))
            {
                return As<uint8_t>();
            }
            else if constexpr (Signed && (Size == 2))
            {
                return As<int16_t>();
            }
            else if constexpr (!Signed && (Size == 2))
            {
                return As<uint16_t>();
            }
            else if constexpr (Signed && (Size == 4))
            {
                return As<int32_t>();
            }
            else if constexpr (!Signed && (Size == 4))
            {
                return As<uint32_t>();
            }
            else if constexpr (Signed && (Size == 8))
            {
                return As<int64_t>();
            }
            else if constexpr (!Signed && (Size == 8))
            {
                return As<uint64_t>();
            }
        }

    private:
        template <typename T>
        ALWAYS_INLINE typename std::enable_if<(Signed == std::is_signed<T>::value) && (Size == sizeof(T)), T>::type As() const
        {
            return *reinterpret_cast<const T*>(_val);  // No need to revert endian.
        }

        char _val[Size];
    };

    template <uint8_t Size> using SignedNumeric = Numeric<true, Size>;
    template <uint8_t Size> using UnsignedNumeric = Numeric<false, Size>;

    template <uint8_t Size, uint8_t NumOfDecimals>
    class Price
    {
    public:
        ALWAYS_INLINE auto RawValue() const
        {
            return _val.Value();
        }

        ALWAYS_INLINE double Value() const
        {
            return _val.Value() * _multiplier;
        }

    private:
        SignedNumeric<Size> _val;
        static constexpr double _multiplier {1.0 / std::pow(10, NumOfDecimals) };  // Multiplication is much faster than division for floating-point numbers.
    };

    template <uint16_t Size, char PadChar = ' '>
    class Alpha
    {
    public:
        ALWAYS_INLINE std::string_view Value() const
        {
            uint16_t i = Size;
            while ((--i >= 0) && (_val[i] == PadChar)) {}
            return std::string_view(_val, i + 1);
        }

    private:
        char _val[Size];
    };

#pragma pack(pop)
}

#endif // _VIVCOURT_TYPES_H_
