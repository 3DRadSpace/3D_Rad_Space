#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents a 3D point with integer coordinates.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Point3
	{
		explicit constexpr Point3(int x = 0, int y = 0, int z = 0) : X(x), Y(y), Z(z) {};
		explicit constexpr Point3(std::initializer_list<int> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0), 
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0), 
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0) 
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
		/// Adds another point to this point in-place.
		/// </summary>
		/// <param name="p">The point to add.</param>
		/// <returns>A reference to this point after addition.</returns>
		Point3 operator +=(const Point3& p);
		/// <summary>
		/// Adds another point to this point and returns the result.
		/// </summary>
		/// <param name="p">The point to add.</param>
		/// <returns>The resulting point after addition.</returns>
		Point3 operator +(const Point3& p) const;

		/// <summary>
		/// Subtracts another point from this point in-place.
		/// </summary>
		/// <param name="p">The point to subtract.</param>
		/// <returns>A reference to this point after subtraction.</returns>
		Point3 operator -=(const Point3& p);
		/// <summary>
		/// Subtracts another point from this point and returns the result.
		/// </summary>
		/// <param name="p">The point to subtract.</param>
		/// <returns>The resulting point after subtraction.</returns>
		Point3 operator -(const Point3& p) const;
		/// <summary>
		///	Inverts the coordinates of this point and returns the result.
		/// </summary>
		/// <returns>The resulting point after inversion.</returns>
		Point3 operator -();

		/// <summary>
		/// Multiplies this point by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>A reference to this point after multiplication.</returns>
		Point3 operator *=(float s);
		/// <summary>
		/// Multiplies this point by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>The resulting point after multiplication.</returns>
		Point3 operator *(float s) const;

		/// <summary>
		/// Divides this point by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>A reference to this point after division.</returns>
		Point3 operator /=(float s);
		/// <summary>
		/// Divides this point by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>The resulting point after division.</returns>
		Point3 operator /(float s) const;

		/// <summary>
		/// Compares this point with another point for equality.
		/// </summary>
		/// <returns>default strong ordering</returns>
		auto operator <=>(const Point3&) const noexcept = default;

		/// <summary>
		/// Converts this point to a Vector3 representation.
		/// </summary>
		/// <returns>The floating point representation of this point.</returns>
		operator Engine3DRadSpace::Math::Vector3() const;
	};
}

/// <summary>
/// Multiplies a point by a scalar.
/// </summary>
/// <param name="s">The scalar to multiply by.</param>
/// <param name="p">The point to multiply.</param>
/// <returns>The resulting point after multiplication.</returns>
Engine3DRadSpace::Math::Point3 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point3& p);
