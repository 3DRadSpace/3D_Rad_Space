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
		float X, Y, Z, W;

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

		float Length() const noexcept;
		float LengthSquared() const noexcept;
		Quaternion& Normalize();
		Quaternion& Conjugate() noexcept;
		/// <summary>
		/// Creates an inverse Quaternion
		/// </summary>
		/// <returns></returns>
		Quaternion& Inverse();

		float Dot(const Quaternion& q) const noexcept;
		static float Dot(const Quaternion& a, const Quaternion& b);

		float& Re() noexcept;
		float Re() const noexcept;
		Vector3 Im() const noexcept;
		
		Vector3 ToYawPitchRoll() const;

		Quaternion& Hadamard(const Quaternion& q);

		Quaternion& operator-() noexcept;

		Quaternion operator +(const Quaternion& q) const noexcept;
		Quaternion& operator +=(const Quaternion& q) noexcept;

		Quaternion operator -(const Quaternion& q) const noexcept;
		Quaternion& operator -=(const Quaternion& q) noexcept;

		Quaternion operator *(const Quaternion& q) const noexcept;
		Quaternion& operator *=(const Quaternion& q) noexcept;

		Quaternion operator*(float s) const noexcept;
		Quaternion& operator *=(float s) noexcept;

		Quaternion operator /(float s) const;
		Quaternion& operator /=(float s);

		auto operator <=>(const Quaternion& q) const noexcept = default;
	};

	Quaternion E3DRSP_MATH_EXPORT operator /(float f, const Quaternion& q);
	Quaternion E3DRSP_MATH_EXPORT operator *(float s, const Quaternion& q) noexcept;
}

