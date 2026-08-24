#pragma once
#include "../Core/Libs.hpp"
#include "Vector2.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		/// <summary>
		/// Represents a 2D point with integer coordinates.
		/// </summary>
		struct E3DRSP_MATH_EXPORT Point
		{
			explicit constexpr Point(int x = 0, int y = 0) : X(x), Y(y) {};
			explicit constexpr Point(std::initializer_list<int> lst) :
				X(lst.size() > 0 ? *(lst.begin()) : 0),
				Y(lst.size() > 1 ? *(lst.begin() + 1) : 0)
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
			/// Adds another point to this point in-place.
			/// </summary>
			/// <param name="p">The point to add.</param>
			/// <returns>A reference to this point after addition.</returns>
			Point operator +=(const Point& p);
			/// <summary>
			/// Adds another point to this point and returns the result.
			/// </summary>
			/// <param name="p">The point to add.</param>
			/// <returns>The resulting point after addition.</returns>
			Point operator +(const Point &p) const;
			
			/// <summary>
			/// Subtracts another point from this point in-place.
			/// </summary>
			/// <param name="p">The point to subtract.</param>
			/// <returns>A reference to this point after subtraction.</returns>
			Point operator -=(const Point& p);
			/// <summary>
			/// Subtracts another point from this point and returns the result.
			/// </summary>
			/// <param name="p">The point to subtract.</param>
			/// <returns>The resulting point after subtraction.</returns>
			Point operator -(const Point &p) const;
			/// <summary>
			///	Inverts the coordinates of this point and returns the result.
			/// </summary>
			/// <returns>The resulting point after inversion.</returns>
			Point operator -();

			/// <summary>
			/// Multiplies this point by a scalar in-place.
			/// </summary>
			/// <param name="s">The scalar to multiply by.</param>
			/// <returns>A reference to this point after multiplication.</returns>
			Point operator *=(float s);
			/// <summary>
			/// Multiplies this point by a scalar and returns the result.
			/// </summary>
			/// <param name="s">The scalar to multiply by.</param>
			/// <returns>The resulting point after multiplication.</returns>
			Point operator *(float s) const;

			/// <summary>
			/// Divides this point by a scalar in-place.
			/// </summary>
			/// <param name="s">The scalar to divide by.</param>
			/// <returns>A reference to this point after division.</returns>
			Point operator /=(float s);
			/// <summary>
			/// Divides this point by a scalar and returns the result.
			/// </summary>
			/// <param name="s">The scalar to divide by.</param>
			/// <returns>The resulting point after division.</returns>
			Point operator /(float s) const;

			/// <summary>
			/// Compares this point with another point for equality.
			/// </summary>
			/// <param name="p">The point to compare with.</param>
			/// <returns>default strong ordering</returns>
			auto operator <=>(const Point&) const noexcept = default;

			/// <summary>
			/// Converts this point to a Vector2 representation.
			/// </summary>
			/// <returns>The floating point representation of this point.</returns>
			operator Engine3DRadSpace::Math::Vector2() const;
		};
	}
}

Engine3DRadSpace::Math::Point E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point& p);

