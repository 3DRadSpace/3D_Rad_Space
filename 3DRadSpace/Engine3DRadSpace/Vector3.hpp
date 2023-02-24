#pragma once
#include "Libs.hpp"
#include "Quaternion.hpp"
#include "Matrix.hpp"

namespace Engine3DRadSpace::Math
{
	struct Quaternion;
	struct Matrix;

	struct Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {};

		constexpr static Vector3 Zero();
		constexpr static Vector3 UnitX();
		constexpr static Vector3 UnitY();
		constexpr static Vector3 UnitZ();
		constexpr static Vector3 One();

		float Length();
		Vector3 Normalize();

		Vector3& operator +=(const Vector3& v);
		Vector3 operator +(const Vector3& v) const;
		Vector3& operator -=(const Vector3& v);
		Vector3 operator -(const Vector3& v) const;
		Vector3 operator-();

		Vector3& operator *=(float s);
		Vector3 operator*(float s) const;

		static Vector3 Cross(const Vector3& v1, const Vector3 &v2);
		float Dot(const Vector3& v);

		Vector3 Transform(const Quaternion& q);
		Vector3 Transform(const Matrix& m);

		auto operator <=>(const Vector3& v) const = default;
	};

	static Vector3& operator *=(float s, Vector3& v);
	static Vector3 operator *(float s, const Vector3& v);
}
