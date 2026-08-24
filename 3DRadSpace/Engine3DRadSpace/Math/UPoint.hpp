#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		/// <summary>
		/// Represents a 2D point with unsigned integer coordinates.
		/// </summary>
		struct E3DRSP_MATH_EXPORT UPoint
		{
			explicit constexpr UPoint(unsigned x = 0, unsigned y = 0) : X(x), Y(y) {};
			explicit constexpr UPoint(std::initializer_list<unsigned> lst) :
				X(lst.size() > 0 ? *(lst.begin()) : 0),
				Y(lst.size() > 1 ? *(lst.begin() + 1) : 0)
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
			/// Adds another point to this point in-place.
			/// </summary>
			/// <param name="p">The point to add.</param>
			/// <returns>A reference to this point after addition.</returns>
			UPoint operator +=(const UPoint& p);
			/// <summary>
			/// Adds another point to this point and returns the result.
			/// </summary>
			/// <param name="p">The point to add.</param>
			/// <returns>The resulting point after addition.</returns>
			UPoint operator +(const UPoint&p) const;

			/// <summary>
			/// Subtracts another point from this point in-place.
			/// </summary>
			/// <param name="p">The point to subtract.</param>
			/// <returns>A reference to this point after subtraction.</returns>
			UPoint operator -=(const UPoint& p);
			/// <summary>
			/// Subtracts another point from this point and returns the result.
			/// </summary>
			/// <param name="p">The point to subtract.</param>
			/// <returns>The resulting point after subtraction.</returns>
			UPoint operator -(const UPoint&p) const;

			/// <summary>
			/// Multiplies this point by a scalar in-place.
			/// </summary>
			/// <param name="s">The scalar to multiply by.</param>
			/// <returns>A reference to this point after multiplication.</returns>
			UPoint operator *=(float s);
			/// <summary>
			/// Multiplies this point by a scalar and returns the result.
			/// </summary>
			/// <param name="s">The scalar to multiply by.</param>
			/// <returns>The resulting point after multiplication.</returns>
			UPoint operator *(float s) const;

			/// <summary>
			/// Divides this point by a scalar in-place.
			/// </summary>
			/// <param name="s">The scalar to divide by.</param>
			/// <returns>A reference to this point after division.</returns>
			UPoint operator /=(float s);
			/// <summary>
			/// Divides this point by a scalar and returns the result.
			/// </summary>
			/// <param name="s">The scalar to divide by.</param>
			/// <returns>The resulting point after division.</returns>
			UPoint operator /(float s) const;

			/// <summary>
			/// Compares this point with another point for equality.
			/// </summary>
			/// <returns>default strong ordering</returns>
			auto operator <=>(const UPoint&) const noexcept = default;
		};
	}
}

/// <summary>
/// Multiplies a point by a scalar.
/// </summary>
/// <param name="s">The scalar to multiply by.</param>
/// <param name="p">The point to multiply.</param>
/// <returns>The resulting point after multiplication.</returns>
Engine3DRadSpace::Math::UPoint E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::UPoint& p);

