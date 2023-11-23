#pragma once
#include <type_traits>
#include <concepts>

template<typename N>
concept signed_integer = std::is_same_v<N, int8_t> || std::is_same_v<N, int16_t> || std::is_same_v<N, int32_t> || std::is_same_v<N, int64_t>;

template<typename N>
concept unsigned_integer = std::is_same_v<N, uint8_t> || std::is_same_v<N, uint16_t> || std::is_same_v<N, uint32_t> || std::is_same_v<N, uint64_t>;

template<typename N>
concept arithmetic = unsigned_integer<N> || signed_integer<N> || std::floating_point<N>;

template<typename T>
concept primitive = std::integral<T> || std::floating_point<T>;