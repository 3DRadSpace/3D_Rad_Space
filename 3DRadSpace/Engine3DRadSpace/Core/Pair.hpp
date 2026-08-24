#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// A pair of values.
	/// </summary>
	/// <typeparam name="T1">Type of the first value</typeparam>
	/// <typeparam name="T2">Type of the second value</typeparam>
	template<typename T1, typename T2>
	struct Pair
	{
		using FirstType = T1;
		using SecondType = T2;

		/// <summary>
		/// The first value of the pair.
		/// </summary>
		T1 First;
		/// <summary>
		///	The second value of the pair.
		/// </summary>
		T2 Second;

		/// <summary>
		/// Constructs an pair with default-initialized values.
		/// </summary>
		constexpr Pair() = default;
		/// <summary>
		///	Constructs a pair with the specified values.
		/// </summary>
		/// <param name="first">First value of the pair.</param>
		/// <param name="second">Second value of the pair.</param>
		constexpr Pair(const T1& first, const T2& second) : First(first), Second(second) {}
		/// <summary>
		/// Constructs a pair that takes ownership of the specified values.
		/// </summary>
		/// <param name="first">First value of the pair.</param>
		/// <param name="second">Second value of the pair.</param>
		constexpr Pair(T1&& first, T2&& second) : First(std::move(first)), Second(std::move(second)) {}

		constexpr auto operator <=>(const Pair&) const = default;
	};
}