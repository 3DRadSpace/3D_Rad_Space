#pragma once
#include "../Libs.hpp"
#include "Quaternion.hpp"
#include "Matrix4x4.hpp"

namespace Engine3DRadSpace::Math
{
	struct Quaternion;
	struct Matrix4x4;

	struct DLLEXPORT Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {};

		static Vector3 Zero();
		static Vector3 UnitX();
		static Vector3 UnitY();
		static Vector3 UnitZ();
		static Vector3 One();

		static Vector3 Up();
		static Vector3 Down();
		static Vector3 Forward();
		static Vector3 Backward();
		static Vector3 Left();
		static Vector3 Right();

		float Length() const;
		float LengthSquared() const;

		Vector3& Normalize();
		static Vector3 Normalize(const Vector3& v);

		Vector3& operator +=(const Vector3& v);
		Vector3 operator +(const Vector3& v) const;
		Vector3& operator -=(const Vector3& v);
		Vector3 operator -(const Vector3& v) const;

		Vector3& operator-();
		Vector3 operator-() const;

		Vector3& operator *=(float s);
		Vector3 operator*(float s) const;

		Vector3& operator /=(float s);
		Vector3 operator /(float s) const;

		Vector3 Cross(const Vector3& v);
		static Vector3 Cross(const Vector3& v1, const Vector3& v2);

		float Dot(const Vector3& v) const;
		static float Dot(const Vector3& a, const Vector3& b);

		Vector3& Transform(const Quaternion& q);
		Vector3& Transform(const Matrix4x4& m);

		static Vector3 Transform(const Vector3& v, const Quaternion& q);
		static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

		//Element-wise product.
		Vector3& Hadamard(const Vector3& v);
		//Element wise product
		static Vector3 Hadamard(const Vector3& a, const Vector3& b);

		auto operator <=>(const Vector3& v) const = default;
	};

	DLLEXPORT Vector3 operator *(float s, const Vector3& v);
	DLLEXPORT Vector3 operator /(float s, const Vector3& v);
}
