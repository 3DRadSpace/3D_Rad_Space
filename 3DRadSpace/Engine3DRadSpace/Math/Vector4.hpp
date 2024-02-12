#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct DLLEXPORT Vector4
	{
		float X, Y, Z, W;

		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : X(x), Y(y), Z(z), W(w) {};
		Vector4(Vector3 v) : X(v.X), Y(v.Y), Z(v.Z), W(1) {};

		static Vector4 UnitX();
		 Vector4 UnitY();
		static Vector4 UnitZ();
		static Vector4 UnitW();
		static Vector4 One();

		float Length() const;
		float LengthSquared() const;

		static float Dot(const Vector4& a, const Vector4 &b);
		float Dot(const Vector4& v) const;

		static Vector4 Hadamard(const Vector4& a, const Vector4& b);
		Vector4& Hadamard(const Vector4& v);

		Vector4 operator+(const Vector4& v) const;
		Vector4& operator+=(const Vector4& v);

		Vector4& operator-();
		Vector4 operator-() const;

		Vector4 operator-(const Vector4& v) const;
		Vector4& operator -=(const Vector4& v);

		Vector4 operator *(float scalar) const;
		Vector4& operator *=(float scalar);

		Vector4 operator /(float f) const;
		Vector4& operator /=(float f);

		Vector4& Transform(const Matrix4x4& m);
		static Vector4 Transform(const Vector4& v, const Matrix4x4& m);

		auto operator <=>(const Vector4& v) const = default;
	};

	Vector4 operator *(float scalar, const Vector4& v);
	Vector4 operator /(float scalar, const Vector4& v);
}
