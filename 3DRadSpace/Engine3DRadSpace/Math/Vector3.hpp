#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Quaternion;
	struct Matrix4x4;
	struct Vector2;

	struct E3DRSP_MATH_EXPORT Vector3
	{
		/// <summary>
		///	X component of the vector.
		/// </summary>
		float X;
		/// <summary>
		///	Y component of the vector.
		/// </summary>
		float Y;
		/// <summary>
		///	Z component of the vector.
		/// </summary>
		float Z;

		/// <summary>
		/// Creates a vector with the specified values. If no values are provided, it creates a zero vector.
		/// </summary>
		/// <param name="x">The X component.</param>
		/// <param name="y">The Y component.</param>
		/// <param name="z">The Z component.</param>
		explicit constexpr Vector3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {};

		/// <summary>
		/// Creates a vector from an initializer list of floats.
		/// </summary>
		/// <param name="lst">The initializer list containing up to 3 values (X, Y, Z).</param>
		explicit constexpr Vector3(std::initializer_list<float> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0.0f),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0.0f),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0.0f)
		{
		};

		/// <summary>
		/// Returns a zero vector (0, 0, 0).
		/// </summary>
		/// <returns>The zero vector.</returns>
		static Vector3 Zero();
		/// <summary>
		/// Returns the unit vector along the X-axis (1, 0, 0).
		/// </summary>
		/// <returns>The unit X vector.</returns>
		static Vector3 UnitX();
		/// <summary>
		/// Returns the unit vector along the Y-axis (0, 1, 0).
		/// </summary>
		/// <returns>The unit Y vector.</returns>
		static Vector3 UnitY();
		/// <summary>
		/// Returns the unit vector along the Z-axis (0, 0, 1).
		/// </summary>
		/// <returns>The unit Z vector.</returns>
		static Vector3 UnitZ();
		/// <summary>
		/// Returns a vector with all components set to 1 (1, 1, 1).
		/// </summary>
		/// <returns>The one vector.</returns>
		static Vector3 One();

		/// <summary>
		/// Returns the up direction unit vector.
		/// </summary>
		/// <returns>The up direction vector.</returns>
		static Vector3 Up();
		/// <summary>
		/// Returns the down direction unit vector.
		/// </summary>
		/// <returns>The down direction vector.</returns>
		static Vector3 Down();
		/// <summary>
		/// Returns the forward direction unit vector.
		/// </summary>
		/// <returns>The forward direction vector.</returns>
		static Vector3 Forward();
		/// <summary>
		/// Returns the backward direction unit vector.
		/// </summary>
		/// <returns>The backward direction vector.</returns>
		static Vector3 Backward();
		/// <summary>
		/// Returns the left direction unit vector.
		/// </summary>
		/// <returns>The left direction vector.</returns>
		static Vector3 Left();
		/// <summary>
		/// Returns the right direction unit vector.
		/// </summary>
		/// <returns>The right direction vector.</returns>
		static Vector3 Right();

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
		/// Normalizes this vector in-place.
		/// </summary>
		/// <returns>A reference to this vector after normalization.</returns>
		Vector3& Normalize();
		/// <summary>
		/// Returns the normalized form of the specified vector.
		/// </summary>
		/// <param name="v">The vector to normalize.</param>
		/// <returns>The normalized vector.</returns>
		static Vector3 Normalize(const Vector3& v);

		/// <summary>
		/// Adds another vector to this vector in-place.
		/// </summary>
		/// <param name="v">The vector to add.</param>
		/// <returns>A reference to this vector after addition.</returns>
		Vector3& operator +=(const Vector3& v);
		/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="v">The vector to add.</param>
		/// <returns>The resulting vector after addition.</returns>
		Vector3 operator +(const Vector3& v) const;
		/// <summary>
		/// Subtracts another vector from this vector in-place.
		/// </summary>
		/// <param name="v">The vector to subtract.</param>
		/// <returns>A reference to this vector after subtraction.</returns>
		Vector3& operator -=(const Vector3& v);
		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="v">The vector to subtract.</param>
		/// <returns>The resulting vector after subtraction.</returns>
		Vector3 operator -(const Vector3& v) const;

		/// <summary>
		/// Negates this vector in-place.
		/// </summary>
		/// <returns>A reference to this vector after negation.</returns>
		Vector3& operator-();
		/// <summary>
		/// Returns the negated form of this vector.
		/// </summary>
		/// <returns>The negated vector.</returns>
		Vector3 operator-() const;

		/// <summary>
		/// Multiplies this vector by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar value.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		Vector3& operator *=(float s);
		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar value.</param>
		/// <returns>The resulting scaled vector.</returns>
		Vector3 operator*(float s) const;

		/// <summary>
		/// Divides this vector by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar value.</param>
		/// <returns>A reference to this vector after division.</returns>
		Vector3& operator /=(float s);
		/// <summary>
		/// Divides this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar value.</param>
		/// <returns>The resulting vector after division.</returns>
		Vector3 operator /(float s) const;

		/// <summary>
		/// Computes the cross product of this vector with another vector in-place.
		/// </summary>
		/// <param name="v">The other vector.</param>
		/// <returns>A reference to this vector after the cross product.</returns>
		Vector3& Cross(const Vector3& v);
		/// <summary>
		/// Computes the cross product of two vectors.
		/// </summary>
		/// <param name="v1">The first vector.</param>
		/// <param name="v2">The second vector.</param>
		/// <returns>The resulting cross product vector.</returns>
		static Vector3 Cross(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// Computes the dot product of this vector with another vector.
		/// </summary>
		/// <param name="v">The other vector.</param>
		/// <returns>The dot product.</returns>
		float Dot(const Vector3& v) const;
		/// <summary>
		/// Computes the dot product of two vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The dot product.</returns>
		static float Dot(const Vector3& a, const Vector3& b);

		/// <summary>
		/// Transforms this vector in-place by the specified quaternion rotation.
		/// </summary>
		/// <param name="q">The quaternion to transform by.</param>
		/// <returns>A reference to this vector after transformation.</returns>
		Vector3& Transform(const Quaternion& q);
		/// <summary>
		/// Transforms this vector in-place by the specified matrix.
		/// </summary>
		/// <param name="m">The matrix to transform by.</param>
		/// <returns>A reference to this vector after transformation.</returns>
		Vector3& Transform(const Matrix4x4& m);

		/// <summary>
		/// Transforms the specified vector by the given quaternion rotation.
		/// </summary>
		/// <param name="v">The vector to transform.</param>
		/// <param name="q">The quaternion to transform by.</param>
		/// <returns>The resulting transformed vector.</returns>
		static Vector3 Transform(const Vector3& v, const Quaternion& q);
		/// <summary>
		/// Transforms the specified vector by the given matrix.
		/// </summary>
		/// <param name="v">The vector to transform.</param>
		/// <param name="m">The matrix to transform by.</param>
		/// <returns>The resulting transformed vector.</returns>
		static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

		//Element-wise product.
		Vector3& Hadamard(const Vector3& v);
		//Element wise product
		static Vector3 Hadamard(const Vector3& a, const Vector3& b);

		/// <summary>
		/// Returns a vector with the components swizzled to (X, X).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 XX() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (X, Y).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 XY() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (X, Z).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 XZ() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (Y, X).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 YX() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (Y, Y).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 YY() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (Y, Z).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 YZ() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (Z, X).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 ZX() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (Z, Y).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 ZY() const noexcept;
		/// <summary>
		/// Returns a vector with the components swizzled to (Z, Z).
		/// </summary>
		/// <returns>The swizzled vector.</returns>
		Vector2 ZZ() const noexcept;

		/// <summary>
		/// Compares this vector with another vector for equality.
		/// </summary>
		/// <param name="v">The vector to compare with.</param>
		/// <returns>default ordering</returns>
		auto operator <=>(const Vector3& v) const = default;
	};

	/// <summary>
	/// Multiplies a vector by a scalar.
	/// </summary>
	/// <param name="s">The scalar value.</param>
	/// <param name="v">The vector to multiply.</param>
	/// <returns>The resulting scaled vector.</returns>
	Vector3 E3DRSP_MATH_EXPORT operator *(float s, const Vector3& v);
	/// <summary>
	/// Divides a scalar by a vector, component-wise.
	/// </summary>
	/// <param name="s">The scalar value.</param>
	/// <param name="v">The vector to divide by.</param>
	/// <returns>The resulting vector.</returns>
	Vector3 E3DRSP_MATH_EXPORT operator /(float s, const Vector3& v);
}
