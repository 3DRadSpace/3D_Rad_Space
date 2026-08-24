#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT Vector4
	{
		/// <summary>
		///	X, Y, Z, W components of the vector.
		/// </summary>
		float X, Y, Z, W;

		/// <summary>
		/// Creates a vector with the specified values. If no values are provided, it creates a zero vector.
		/// </summary>
		/// <param name="x">The X component.</param>
		/// <param name="y">The Y component.</param>
		/// <param name="z">The Z component.</param>
		/// <param name="w">The W component.</param>
		explicit constexpr Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : X(x), Y(y), Z(z), W(w) {};
		/// <summary>
		/// Creates a vector from a Vector3, setting W to 1.
		/// </summary>
		/// <param name="v">The source Vector3.</param>
		explicit constexpr Vector4(Vector3 v) : X(v.X), Y(v.Y), Z(v.Z), W(1) {};
		/// <summary>
		/// Creates a vector from an initializer list of floats.
		/// </summary>
		/// <param name="lst">The initializer list containing up to 4 values (X, Y, Z, W).</param>
		explicit constexpr Vector4(std::initializer_list<float> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0.0f),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0.0f),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0.0f),
			W(lst.size() > 3 ? *(lst.begin() + 3) : 0.0f)
		{
		};

		/// <summary>
		/// Returns a zero vector (0, 0, 0, 0).
		/// </summary>
		/// <returns>The zero vector.</returns>
		static Vector4 Zero();
		/// <summary>
		/// Returns the unit vector along the X-axis (1, 0, 0, 0).
		/// </summary>
		/// <returns>The unit X vector.</returns>
		static Vector4 UnitX();
		/// <summary>
		/// Returns the unit vector along the Y-axis (0, 1, 0, 0).
		/// </summary>
		/// <returns>The unit Y vector.</returns>
		static Vector4 UnitY();
		/// <summary>
		/// Returns the unit vector along the Z-axis (0, 0, 1, 0).
		/// </summary>
		/// <returns>The unit Z vector.</returns>
		static Vector4 UnitZ();
		/// <summary>
		/// Returns the unit vector along the W-axis (0, 0, 0, 1).
		/// </summary>
		/// <returns>The unit W vector.</returns>
		static Vector4 UnitW();
		/// <summary>
		/// Returns a vector with all components set to 1 (1, 1, 1, 1).
		/// </summary>
		/// <returns>The one vector.</returns>
		static Vector4 One();

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
		Vector4& Normalize();

		/// <summary>
		/// Computes the dot product of two vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The dot product.</returns>
		static float Dot(const Vector4& a, const Vector4 &b);
		/// <summary>
		/// Computes the dot product of this vector with another vector.
		/// </summary>
		/// <param name="v">The other vector.</param>
		/// <returns>The dot product.</returns>
		float Dot(const Vector4& v) const;

		/// <summary>
		/// Element-wise (Hadamard) product of two vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The resulting vector after Hadamard multiplication.</returns>
		static Vector4 Hadamard(const Vector4& a, const Vector4& b);
		/// <summary>
		/// Element-wise (Hadamard) multiplication of this vector with another vector.
		/// </summary>
		/// <param name="v">The vector to multiply with.</param>
		/// <returns>A reference to this vector after Hadamard multiplication.</returns>
		Vector4& Hadamard(const Vector4& v);

		/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="v">The vector to add.</param>
		/// <returns>The resulting vector after addition.</returns>
		Vector4 operator+(const Vector4& v) const;
		/// <summary>
		/// Adds another vector to this vector in-place.
		/// </summary>
		/// <param name="v">The vector to add.</param>
		/// <returns>A reference to this vector after addition.</returns>
		Vector4& operator+=(const Vector4& v);

		/// <summary>
		/// Negates this vector in-place.
		/// </summary>
		/// <returns>A reference to this vector after negation.</returns>
		Vector4& operator-();
		/// <summary>
		/// Returns the negated form of this vector.
		/// </summary>
		/// <returns>The negated vector.</returns>
		Vector4 operator-() const;

		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="v">The vector to subtract.</param>
		/// <returns>The resulting vector after subtraction.</returns>
		Vector4 operator-(const Vector4& v) const;
		/// <summary>
		/// Subtracts another vector from this vector in-place.
		/// </summary>
		/// <param name="v">The vector to subtract.</param>
		/// <returns>A reference to this vector after subtraction.</returns>
		Vector4& operator -=(const Vector4& v);

		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value.</param>
		/// <returns>The resulting scaled vector.</returns>
		Vector4 operator *(float scalar) const;
		/// <summary>
		/// Multiplies this vector by a scalar in-place.
		/// </summary>
		/// <param name="scalar">The scalar value.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		Vector4& operator *=(float scalar);

		/// <summary>
		/// Divides this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="f">The scalar value.</param>
		/// <returns>The resulting vector after division.</returns>
		Vector4 operator /(float f) const;
		/// <summary>
		/// Divides this vector by a scalar in-place.
		/// </summary>
		/// <param name="f">The scalar value.</param>
		/// <returns>A reference to this vector after division.</returns>
		Vector4& operator /=(float f);

		/// <summary>
		/// Transforms this vector in-place by the specified matrix.
		/// </summary>
		/// <param name="m">The matrix to transform by.</param>
		/// <returns>A reference to this vector after transformation.</returns>
		Vector4& Transform(const Matrix4x4& m);
		/// <summary>
		/// Transforms the specified vector by the given matrix.
		/// </summary>
		/// <param name="v">The vector to transform.</param>
		/// <param name="m">The matrix to transform by.</param>
		/// <returns>The resulting transformed vector.</returns>
		static Vector4 Transform(const Vector4& v, const Matrix4x4& m);

		/// <summary>
		/// Compares this vector with another vector for equality.
		/// </summary>
		/// <param name="v">The vector to compare with.</param>
		/// <returns>default ordering</returns>
		auto operator <=>(const Vector4& v) const = default;
	};

	/// <summary>
	/// Multiplies a vector by a scalar.
	/// </summary>
	/// <param name="scalar">The scalar value.</param>
	/// <param name="v">The vector to multiply.</param>
	/// <returns>The resulting scaled vector.</returns>
	Vector4 E3DRSP_MATH_EXPORT operator *(float scalar, const Vector4& v);
	/// <summary>
	/// Divides a scalar by a vector, component-wise.
	/// </summary>
	/// <param name="scalar">The scalar value.</param>
	/// <param name="v">The vector to divide by.</param>
	/// <returns>The resulting vector.</returns>
	Vector4 E3DRSP_MATH_EXPORT operator /(float scalar, const Vector4& v);
}
