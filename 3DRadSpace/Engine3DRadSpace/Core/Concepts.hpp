#pragma once
#include <type_traits>
#include <concepts>

/// <summary>
/// Is N an signed integer type? (int8_t, int16_t, int32_t, int64_t)
/// </summary>
template<typename N>
concept signed_integer = std::is_same_v<N, int8_t> || std::is_same_v<N, int16_t> || std::is_same_v<N, int32_t> || std::is_same_v<N, int64_t>;

/// <summary>
/// Is N an unsigned integer type? (uint8_t, uint16_t, uint32_t, uint64_t)
/// </summary>
template<typename N>
concept unsigned_integer = std::is_same_v<N, uint8_t> || std::is_same_v<N, uint16_t> || std::is_same_v<N, uint32_t> || std::is_same_v<N, uint64_t>;

/// <summary>
/// Is N an arithmetic type? (signed_integer, unsigned_integer, or floating_point)
/// </summary>
template<typename N>
concept arithmetic = unsigned_integer<N> || signed_integer<N> || std::floating_point<N>;

/// <summary>
/// Is T a primitive type? (integral or floating_point)
/// </summary>
template<typename T>
concept primitive = std::integral<T> || std::floating_point<T>;

/// <summary>
/// Is E an enumeration type?
/// </summary>
template<typename E>
concept c_enum = std::is_enum_v<E>;