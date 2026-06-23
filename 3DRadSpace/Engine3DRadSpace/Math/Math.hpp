#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Converts degrees to radians.
	/// </summary>
	/// <typeparam name="T">Floating type</typeparam>
	/// <param name="degrees">Angle in degrees</param>
	/// <returns>Angle in radians</returns>
	template<typename T> 
	constexpr T ToRadians(T degrees)
	{
		return static_cast<T>(std::numbers::pi * degrees / 180);
	}

	/// <summary>
	/// Converts radians to degrees.
	/// </summary>
	/// <typeparam name="T">Floating type</typeparam>
	/// <param name="radians">Angle in radians</param>
	/// <returns>Angle in degrees</returns>
	template<typename T>
	constexpr T ToDegrees(T radians)
	{
		return static_cast<T>(radians * 180 / std::numbers::pi);
	}

	/// <summary>
	/// Performs a Catmull-Rom interpolation.
	/// </summary>
	/// <param name="value1">The first value.</param>
	/// <param name="value2">The second value.</param>
	/// <param name="value3">The third value.</param>
	/// <param name="value4">The fourth value.</param>
	/// <param name="amount">The interpolation amount.</param>
	/// <returns>The interpolated value.</returns>
	constexpr double E3DRSP_MATH_EXPORT CatmullRom(double value1, double value2, double value3, double value4, double amount);
	/// <summary>
	/// Performs a Hermite spline interpolation between two values with specified tangents.
	/// </summary>
	/// <param name="value1">The first value.</param>
	/// <param name="tangent1">The tangent of the first value.</param>
	/// <param name="value2">The second value.</param>
	/// <param name="tangent2">The tangent of the second value.</param>
	/// <param name="amount">The interpolation amount.</param>
	/// <returns>The interpolated value.</returns>
	constexpr double E3DRSP_MATH_EXPORT Hermite(double value1, double tangent1, double value2, double tangent2, double amount);

	/// <summary>
	/// Axis aligned bounding box check for one single axis.
	/// </summary>
	/// <param name="p1">The position of the first box.</param>
	/// <param name="w1">The width of the first box.</param>
	/// <param name="p2">The position of the second box.</param>
	/// <param name="w2">The width of the second box.</param>
	/// <returns>True if the boxes overlap, false otherwise.</returns>
	constexpr bool E3DRSP_MATH_EXPORT AABB(float p1, float w1, float p2, float w2);

	/// <summary>
	/// Axis aligned bounding box check for one single axis.
	/// </summary>
	/// <param name="p1">The position of the first box.</param>
	/// <param name="w1">The width of the first box.</param>
	/// <param name="p2">The position of the second box.</param>
	/// <param name="w2">The width of the second box.</param>
	/// <returns>True if the boxes overlap, false otherwise.</returns>
	constexpr bool E3DRSP_MATH_EXPORT AABB(double p1, double w1, double p2, double w2);

	/// <summary>
	/// Performs a smooth step interpolation between two values.
	/// </summary>
	/// <remarks>
	/// Same as Hermite(value1, 0, value2, 0, result).
	/// </remarks>
	/// <param name="value1">The first value.</param>
	/// <param name="value2">The second value.</param>
	/// <param name="amount">The interpolation amount.</param>
	/// <returns>The interpolated value.</returns>
	constexpr double E3DRSP_MATH_EXPORT SmoothStep(double value1, double value2, double amount);

	/// <summary>
	/// Rectified Linear Unit. Activation function usually used in neural networks, but it is a shortcut to max(0, x).
	/// </summary>
	/// <param name="x">Input.</param>
	/// <returns>If x > 0 otherwise 0.</returns>
	constexpr double E3DRSP_MATH_EXPORT ReLU(double x);

	constexpr bool E3DRSP_MATH_EXPORT WithinEpsilon(float a, float b);
}