#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents a 3D point with unsigned integer coordinates.
	/// </summary>
	struct E3DRSP_MATH_EXPORT UPoint3
	{
		explicit constexpr UPoint3(
			unsigned x = 0,
			unsigned y = 0,
			unsigned z = 0
		) : X(x), Y(y), Z(z) 
		{
		};

		explicit constexpr UPoint3(std::initializer_list<unsigned> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0)
		{
		};

		/// <summary>
		///	X coordinate of the point.
		/// </summary>
		unsigned X;
		/// <summary>
		///	Y coordinate of the point.
		/// </summary>
		unsigned Y;
		/// <summary>
		///	Z coordinate of the point.
		/// </summary>
		unsigned Z;

		/// <summary>
		/// Adds another point to this point in-place.
		/// </summary>
		/// <param name="p">The point to add.</param>
		/// <returns>A reference to this point after addition.</returns>
		UPoint3 operator +=(const UPoint3& p);
		/// <summary>
		/// Adds another point to this point and returns the result.
		/// </summary>
		/// <param name="p">The point to add.</param>
		/// <returns>The resulting point after addition.</returns>
		UPoint3 operator +(const UPoint3& p) const;

		/// <summary>
		/// Subtracts another point from this point in-place.
		/// </summary>
		/// <param name="p">The point to subtract.</param>
		/// <returns>A reference to this point after subtraction.</returns>
		UPoint3 operator -=(const UPoint3& p);
		/// <summary>
		/// Subtracts another point from this point and returns the result.
		/// </summary>
		/// <param name="p">The point to subtract.</param>
		/// <returns>The resulting point after subtraction.</returns>
		UPoint3 operator -(const UPoint3& p) const;

		/// <summary>
		/// Multiplies this point by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>A reference to this point after multiplication.</returns>
		UPoint3 operator *=(float s);
		/// <summary>
		/// Multiplies this point by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>The resulting point after multiplication.</returns>
		UPoint3 operator *(float s) const;

		/// <summary>
		/// Divides this point by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>A reference to this point after division.</returns>
		UPoint3 operator /=(float s);
		/// <summary>
		/// Divides this point by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>The resulting point after division.</returns>
		UPoint3 operator /(float s) const;

		/// <summary>
		/// Compares this point with another point for equality.
		/// </summary>
		/// <returns>default strong ordering</returns>
		auto operator <=>(const UPoint3&) const noexcept = default;
	};
}

/// <summary>
/// Multiplies a point by a scalar.
/// </summary>
/// <param name="s">The scalar to multiply by.</param>
/// <param name="p">The point to multiply.</param>
/// <returns>The resulting point after multiplication.</returns>
Engine3DRadSpace::Math::UPoint3 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::UPoint3& p);
