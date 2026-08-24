#pragma once
#include "../Core/Libs.hpp"
#include "Vector4.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents a 4D point with integer coordinates.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Point4
	{
		explicit constexpr Point4(int x = 0, int y = 0, int z = 0, int w = 0) : X(x), Y(y), Z(z), W(w) {};
		explicit constexpr Point4(std::initializer_list<int> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0),
			W(lst.size() > 3 ? *(lst.begin() + 3) : 0)
		{
		};

		/// <summary>
		///	X coordinate of the point.
		/// </summary>
		int X;
		/// <summary>
		///	Y coordinate of the point.
		/// </summary>
		int Y;
		/// <summary>
		///	Z coordinate of the point.
		/// </summary>
		int Z;
		/// <summary>
		///	W coordinate of the point.
		/// </summary>
		int W;

		/// <summary>
		/// Adds another point to this point in-place.
		/// </summary>
		/// <param name="p">The point to add.</param>
		/// <returns>A reference to this point after addition.</returns>
		Point4 operator +=(const Point4& p);
		/// <summary>
		/// Adds another point to this point and returns the result.
		/// </summary>
		/// <param name="p">The point to add.</param>
		/// <returns>The resulting point after addition.</returns>
		Point4 operator +(const Point4& p) const;

		/// <summary>
		/// Subtracts another point from this point in-place.
		/// </summary>
		/// <param name="p">The point to subtract.</param>
		/// <returns>A reference to this point after subtraction.</returns>
		Point4 operator -=(const Point4& p);
		/// <summary>
		/// Subtracts another point from this point and returns the result.
		/// </summary>
		/// <param name="p">The point to subtract.</param>
		/// <returns>The resulting point after subtraction.</returns>
		Point4 operator -(const Point4& p) const;
		/// <summary>
		///	Inverts the coordinates of this point and returns the result.
		/// </summary>
		/// <returns>The resulting point after inversion.</returns>
		Point4 operator -();

		/// <summary>
		/// Multiplies this point by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>A reference to this point after multiplication.</returns>
		Point4 operator *=(float s);
		/// <summary>
		/// Multiplies this point by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>The resulting point after multiplication.</returns>
		Point4 operator *(float s) const;

		/// <summary>
		/// Divides this point by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>A reference to this point after division.</returns>
		Point4 operator /=(float s);
		/// <summary>
		/// Divides this point by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>The resulting point after division.</returns>
		Point4 operator /(float s) const;

		/// <summary>
		/// Compares this point with another point for equality.
		/// </summary>
		/// <returns>default strong ordering</returns>
		auto operator <=>(const Point4&) const noexcept = default;

		/// <summary>
		/// Converts this point to a Vector4 representation.
		/// </summary>
		/// <returns>The floating point representation of this point.</returns>
		operator Engine3DRadSpace::Math::Vector4() const;
	};
}

/// <summary>
/// Multiplies a point by a scalar.
/// </summary>
/// <param name="s">The scalar to multiply by.</param>
/// <param name="p">The point to multiply.</param>
/// <returns>The resulting point after multiplication.</returns>
Engine3DRadSpace::Math::Point4 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point4& p);
