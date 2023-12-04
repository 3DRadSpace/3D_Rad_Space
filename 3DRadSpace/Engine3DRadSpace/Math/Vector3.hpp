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

		constexpr Vector3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {};

		constexpr static Vector3 Zero();
		constexpr static Vector3 UnitX();
		constexpr static Vector3 UnitY();
		constexpr static Vector3 UnitZ();
		constexpr static Vector3 One();

		constexpr static Vector3 Up();
		constexpr static Vector3 Down();
		constexpr static Vector3 Forward();
		constexpr static Vector3 Backward();
		constexpr static Vector3 Left();
		constexpr static Vector3 Right();

		float Length() const;
		constexpr float LengthSquared() const;

		Vector3& Normalize();
		static Vector3 Normalize(const Vector3& v);

		constexpr Vector3& operator +=(const Vector3& v);
		constexpr Vector3 operator +(const Vector3& v) const;
		constexpr Vector3& operator -=(const Vector3& v);
		constexpr Vector3 operator -(const Vector3& v) const;

		constexpr Vector3& operator-();
		constexpr Vector3 operator-() const;

		constexpr Vector3& operator *=(float s);
		constexpr Vector3 operator*(float s) const;

		constexpr Vector3& operator /=(float s);
		constexpr Vector3 operator /(float s) const;

		constexpr Vector3 Cross(const Vector3& v);
		constexpr static Vector3 Cross(const Vector3& v1, const Vector3 &v2);
		
		constexpr float Dot(const Vector3 &v) const;
		constexpr static float Dot(const Vector3& a, const Vector3& b);

		constexpr Vector3& Transform(const Quaternion& q);
		constexpr Vector3& Transform(const Matrix4x4& m);

		constexpr static Vector3 Transform(const Vector3& v, const Quaternion& q);
		constexpr static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

		//Element-wise product.
		constexpr Vector3& Hadamard(const Vector3& v);
		//Element wise product
		constexpr static Vector3 Hadamard(const Vector3& a, const Vector3& b);

		auto operator <=>(const Vector3& v) const = default;
	};

	constexpr DLLEXPORT Vector3 operator *(float s, const Vector3& v);
	constexpr DLLEXPORT Vector3 operator /(float s, const Vector3 &v);
}
