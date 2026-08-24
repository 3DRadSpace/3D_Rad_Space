#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Matrix3x3;
	/// <summary>
	/// A 2D vector.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Vector2
	{
		/// <summary>
		///	X and Y components of the vector.
		/// </summary>
		float X, Y;

		/// <summary>
		/// Creates a vector with the specified values. If no values are provided, it creates a zero vector.
		/// </summary>
		/// <param name="x">The X component.</param>
		/// <param name="y">The Y component.</param>
		explicit constexpr Vector2(float x = 0.0f, float y = 0.0f) :X(x), Y(y) {};
		/// <summary>
		/// Creates a vector from an initializer list of floats.
		/// </summary>
		/// <param name="lst">The initializer list containing up to 2 values (X, Y).</param>
		explicit constexpr Vector2(std::initializer_list<float> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0.0f),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0.0f)
		{
		};

		/// <summary>
		/// Returns a zero vector (0, 0).
		/// </summary>
		/// <returns>The zero vector.</returns>
		static Vector2 Zero();
		/// <summary>
		/// Returns the unit vector along the X-axis (1, 0).
		/// </summary>
		/// <returns>The unit X vector.</returns>
		static Vector2 UnitX();
		/// <summary>
		/// Returns the unit vector along the Y-axis (0, 1).
		/// </summary>
		/// <returns>The unit Y vector.</returns>
		static Vector2 UnitY();
		/// <summary>
		/// Returns a vector with all components set to 1 (1, 1).
		/// </summary>
		/// <returns>The one vector.</returns>
		static Vector2 One();

		/// <summary>
		/// Returns the length (magnitude) of this vector.
		/// </summary>
		/// <returns>The length of the vector.</returns>
		float Length() const;
		/// <summary>
		/// Returns the squared length of this vector.
		/// </summary>
		/// <returns>The squared length of the vector.</returns>
		float LengthSquared() const;
		/// <summary>
		/// Returns the angle of this vector in radians, relative to the X-axis.
		/// </summary>
		/// <returns>The angle in radians.</returns>
		float Angle() const;

		/// <summary>
		/// Computes the dot product of this vector with another vector.
		/// </summary>
		/// <param name="v">The other vector.</param>
		/// <returns>The dot product.</returns>
		float Dot(const Vector2 &v) const;
		/// <summary>
		/// Computes the dot product of two vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The dot product.</returns>
		static float Dot(const Vector2& a, const Vector2& b);

		/// <summary>
		/// Normalizes this vector in-place.
		/// </summary>
		/// <returns>A reference to this vector after normalization.</returns>
		Vector2& Normalize();
		/// <summary>
		/// Returns the normalized form of the specified vector.
		/// </summary>
		/// <param name="v">The vector to normalize.</param>
		/// <returns>The normalized vector.</returns>
		static Vector2 Normalize(const Vector2& v);

		/// <summary>
		/// Adds another vector to this vector in-place.
		/// </summary>
		/// <param name="v">The vector to add.</param>
		/// <returns>A reference to this vector after addition.</returns>
		Vector2& operator +=(const Vector2& v);
		/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="v">The vector to add.</param>
		/// <returns>The resulting vector after addition.</returns>
		Vector2 operator +(const Vector2 &v) const;

		/// <summary>
		/// Negates this vector in-place.
		/// </summary>
		/// <returns>A reference to this vector after negation.</returns>
		Vector2& operator-();
		/// <summary>
		/// Returns the negated form of this vector.
		/// </summary>
		/// <returns>The negated vector.</returns>
		Vector2 operator-() const;

		/// <summary>
		/// Subtracts another vector from this vector in-place.
		/// </summary>
		/// <param name="v">The vector to subtract.</param>
		/// <returns>A reference to this vector after subtraction.</returns>
		Vector2& operator -=(const Vector2& v);
		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="v">The vector to subtract.</param>
		/// <returns>The resulting vector after subtraction.</returns>
		Vector2 operator -(const Vector2 &v) const;

		/// <summary>
		/// Computes the dot product of this vector with another vector.
		/// </summary>
		/// <param name="v">The other vector.</param>
		/// <returns>The dot product.</returns>
		float operator*(const Vector2 &v) const;
		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar value.</param>
		/// <returns>The resulting scaled vector.</returns>
		Vector2 operator*(float s) const;
		/// <summary>
		/// Multiplies this vector by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar value.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		Vector2& operator *=(float s);

		/// <summary>
		/// Divides this vector by a scalar in-place.
		/// </summary>
		/// <param name="f">The scalar value.</param>
		/// <returns>A reference to this vector after division.</returns>
		Vector2& operator /=(float f);
		/// <summary>
		/// Divides this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="f">The scalar value.</param>
		/// <returns>The resulting vector after division.</returns>
		Vector2 operator /(float f) const;

		/// <summary>
		/// Converts a normalized vector (in the range [-1, 1]) from screen space to clip space.
		/// </summary>
		/// <param name="norm">The normalized screen space vector.</param>
		/// <returns>The resulting clip space vector.</returns>
		static Vector2 ConvertFromNormalizedScreenSpaceToClipSpace(const Vector2& norm);
		/// <summary>
		/// Converts a point in screen coordinates to clip space, given the screen resolution.
		/// </summary>
		/// <param name="point">The point in screen coordinates.</param>
		/// <param name="resolution">The screen resolution.</param>
		/// <returns>The resulting clip space vector.</returns>
		static Vector2 ConvertFromScreenCoordsToClipSpace(const Vector2& point, const Vector2& resolution);

		/// <summary>
		/// Rotates this vector in-place by the specified angle.
		/// </summary>
		/// <param name="theta">The rotation angle in radians.</param>
		/// <returns>A reference to this vector after rotation.</returns>
		Vector2& RotateBy(float theta);
		/// <summary>
		/// Returns the specified vector rotated by the given angle.
		/// </summary>
		/// <param name="v">The vector to rotate.</param>
		/// <param name="theta">The rotation angle in radians.</param>
		/// <returns>The resulting rotated vector.</returns>
		Vector2 Rotate(const Vector2 &v, float theta);

		/// <summary>
		/// Element-wise (Hadamard) multiplication of this vector with another vector.
		/// </summary>
		/// <param name="v">The vector to multiply with.</param>
		/// <returns>A reference to this vector after Hadamard multiplication.</returns>
		Vector2& Hadamard(const Vector2& v);
		/// <summary>
		/// Element-wise (Hadamard) product of two vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The resulting vector after Hadamard multiplication.</returns>
		static Vector2 Hadamard(const Vector2& a, const Vector2& b);

		/// <summary>
		/// Transforms this vector in-place by the specified matrix.
		/// </summary>
		/// <param name="m">The matrix to transform by.</param>
		/// <returns>A reference to this vector after transformation.</returns>
		Vector2& Transform(const Matrix3x3& m);
		/// <summary>
		/// Transforms the specified vector by the given matrix.
		/// </summary>
		/// <param name="v">The vector to transform.</param>
		/// <param name="m">The matrix to transform by.</param>
		/// <returns>The resulting transformed vector.</returns>
		static Vector2 Transform(const Vector2& v, const Matrix3x3& m);

		/// <summary>
		/// Returns a vector with the components swizzled to (Y, X).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 YX() const noexcept;
	};

	/// <summary>
	/// Multiplies a vector by a scalar.
	/// </summary>
	/// <param name="s">The scalar value.</param>
	/// <param name="v">The vector to multiply.</param>
	/// <returns>The resulting scaled vector.</returns>
	Vector2 E3DRSP_MATH_EXPORT operator*(float s, const Vector2& v);
	/// <summary>
	/// Divides a scalar by a vector, component-wise.
	/// </summary>
	/// <param name="s">The scalar value.</param>
	/// <param name="v">The vector to divide by.</param>
	/// <returns>The resulting vector.</returns>
	Vector2 E3DRSP_MATH_EXPORT operator/(float s, const Vector2& v);
}