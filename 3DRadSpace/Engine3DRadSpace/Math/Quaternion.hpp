#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3;
	struct Matrix4x4;

	struct DLLEXPORT Quaternion
	{
		float X, Y, Z, W;

		constexpr Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : X(x), Y(y), Z(z), W(w) {};

		static Quaternion FromYawPitchRoll(float yaw, float pitch, float roll);
		static Quaternion FromAxisAngle(const Vector3& axis, float angle);
		static Quaternion FromMatrix(const Matrix4x4& m);
		static Quaternion FromVectorToVector(const Vector3& a, const Vector3& b);

		float Length() const;
		Quaternion Normalize();
		constexpr Quaternion Conjugate();
		constexpr Quaternion Inverse();

		constexpr Vector3 Im() const;
		
		Vector3 ToYawPitchRoll() const;

		constexpr Quaternion operator +(const Quaternion &q) const;
		constexpr Quaternion operator +=(const Quaternion &q);

		constexpr Quaternion operator -(const Quaternion& q) const;
		constexpr Quaternion& operator-(const Quaternion& q);

		constexpr Quaternion operator *(const Quaternion &q) const;
		constexpr Quaternion operator *=(const Quaternion &q);

		constexpr Quaternion operator /(float s) const;
		constexpr Quaternion operator /=(float s);

		constexpr auto operator <=>(const Quaternion& q) const = default;
	};

	constexpr Quaternion operator /(float f, const Quaternion& q);
	constexpr Quaternion operator *(float s, const Quaternion& q);
}

