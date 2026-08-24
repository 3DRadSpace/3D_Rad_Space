#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3;
	struct Matrix4x4;

	/// <summary>
	/// A quaternion is a hyper-complex number that represents 3D rotations the same way 2D rotations can be represented by a complex number.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Quaternion
	{
		/// <summary>
		/// The X component of the quaternion.
		/// </summary>
		float X;
		/// <summary>
		/// The Y component of the quaternion.
		/// </summary>
		float Y;
		/// <summary>
		/// The Z component of the quaternion.
		/// </summary>
		float Z;
		/// <summary>
		///	The real/scalar component of the quaternion.
		/// </summary>
		float W;

		explicit constexpr Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : X(x), Y(y), Z(z), W(w) {};
		explicit constexpr Quaternion(std::initializer_list<float> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0.0f),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0.0f),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0.0f),
			W(lst.size() > 3 ? *(lst.begin() + 3) : 1.0f)
		{
		}

		static Quaternion FromYawPitchRoll(float yaw, float pitch, float roll);
		static Quaternion FromAxisAngle(const Vector3& axis, float angle);
		static Quaternion FromMatrix(const Matrix4x4& m);
		static Quaternion BetweenVectors(const Vector3& a, const Vector3& b);
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);

		/// <summary>
		///	Returns the length of the quaternion. The length is defined as the square root of the sum of the squares of its components.
		/// </summary>
		/// <returns>The length of the quaternion.</returns>
		float Length() const noexcept;
		/// <summary>
		///	Returns the lenght of this quaternion squared.
		/// </summary>
		/// <returns>X*X + Y*Y + Z*Z + W*W</returns>
		float LengthSquared() const noexcept;
		Quaternion& Normalize();
		Quaternion& Conjugate() noexcept;
		/// <summary>
		/// Creates an inverse Quaternion
		/// </summary>
		/// <returns>The inverse of this quaternion.</returns>
		Quaternion& Inverse();

		/// <summary>
		/// Returns the dot Product between this quaternion and another quaternion.
		/// </summary>
		/// <param name="q">Other quaternion.</param>
		/// <returns>X * q.X + Y * q.Y + Z * q.Z + W * q.W</returns>
		float Dot(const Quaternion& q) const noexcept;
		/// <summary>
		///	Returns the dot product of two quaternions.
		/// </summary>
		/// <param name="a">The first quaternion.</param>
		/// <param name="b">The second quaternion.</param>
		/// <returns>X * b.X + Y * b.Y + Z * b.Z + W * b.W</returns>
		static float Dot(const Quaternion& a, const Quaternion& b);

		/// <summary>
		///	Returns the real part of this quaternion.
		/// </summary>
		/// <returns>Reference to the W coordinate.</returns>
		float& Re() noexcept;
		/// <summary>
		///	Returns the real part of this quaternion.
		/// </summary>
		/// <returns>The W coordinate.</returns>
		float Re() const noexcept;
		/// <summary>
		/// Returns the imaginary component of this quaternion.
		/// </summary>
		/// <returns>The vector containing the X, Y, and Z components.</returns>
		Vector3 Im() const noexcept;
		
		/// <summary>
		///	Converts this quaternion to yaw, pitch, and roll angles (in radians).
		/// </summary>
		/// <returns>A vector containing the yaw, pitch, and roll angles (in radians).</returns>
		Vector3 ToYawPitchRoll() const;

		/// <summary>
		///	Element wise (Hadamard) multiplication of this quaternion with another quaternion.
		/// </summary>
		/// <param name="q">The quaternion to multiply element-wise.</param>
		/// <returns>A reference to this quaternion after the Hadamard multiplication.</returns>
		Quaternion& Hadamard(const Quaternion& q);

		/// <summary>
		///	Negates this quaternion.
		/// </summary>
		/// <returns>A reference to this quaternion after negation.</returns>
		Quaternion& operator-() noexcept;

		/// <summary>
		/// Adds another quaternion to this quaternion and returns the result.
		/// </summary>
		/// <param name="q">The quaternion to add.</param>
		/// <returns>The resulting quaternion after addition.</returns>
		Quaternion operator +(const Quaternion& q) const noexcept;
		/// <summary>
		/// Adds another quaternion to this quaternion in-place.
		/// </summary>
		/// <param name="q">The quaternion to add.</param>
		/// <returns>A reference to this quaternion after addition.</returns>
		Quaternion& operator +=(const Quaternion& q) noexcept;
		/// <summary>
		/// Subtracts another quaternion from this quaternion and returns the result.
		/// </summary>
		/// <param name="q">The quaternion to subtract.</param>
		/// <returns>The resulting quaternion after subtraction.</returns>	
		Quaternion operator -(const Quaternion& q) const noexcept;
		/// <summary>
		/// Subtracts another quaternion from this quaternion in-place.
		/// </summary>
		/// <param name="q">The quaternion to subtract.</param>
		/// <returns>A reference to this quaternion after subtraction.</returns>
		Quaternion& operator -=(const Quaternion& q) noexcept;
		/// <summary>
		/// Multiplies (composes) this quaternion by another quaternion and returns the result.
		/// </summary>
		/// <param name="q">The quaternion to multiply by.</param>
		/// <returns>The resulting quaternion after multiplication.</returns>
		Quaternion operator *(const Quaternion& q) const noexcept;
		/// <summary>
		///	Multiplies (composes) this quaternion by another quaternion in-place.
		/// </summary>
		/// <param name="q">The quaternion to multiply by.</param>
		/// <returns>A reference to this quaternion after multiplication.</returns>
		Quaternion& operator *=(const Quaternion& q) noexcept;
		/// <summary>
		/// Multiplies this quaternion by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>The resulting quaternion after multiplication.</returns>
		Quaternion operator*(float s) const noexcept;
		/// <summary>
		/// Multiplies this quaternion by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to multiply by.</param>
		/// <returns>A reference to this quaternion after multiplication.</returns>
		Quaternion& operator *=(float s) noexcept;
		/// <summary>
		/// Divides this quaternion by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>The resulting quaternion after division.</returns>
		Quaternion operator /(float s) const;
		/// <summary>
		/// Divides this quaternion by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar to divide by.</param>
		/// <returns>A reference to this quaternion after division.</returns>
		Quaternion& operator /=(float s);
		/// <summary>
		/// Partial ordering comparison between this quaternion and another quaternion. The comparison is based on the lexicographical order of the components (X, Y, Z, W).
		/// </summary>
		/// <param name="q">The quaternion to compare with.</param>
		/// <returns>The result of the partial ordering comparison.</returns>
		auto operator <=>(const Quaternion& q) const noexcept = default;
	};

	Quaternion E3DRSP_MATH_EXPORT operator /(float f, const Quaternion& q);
	Quaternion E3DRSP_MATH_EXPORT operator *(float s, const Quaternion& q) noexcept;
}

