#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct DLLEXPORT Vector4
	{
		float X, Y, Z, W;

		constexpr Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : X(x), Y(y), Z(z), W(w) {};
		constexpr Vector4(Vector3 v) : X(v.X), Y(v.Y), Z(v.Z), W(1) {};

		constexpr static Vector4 UnitX();
		constexpr  Vector4 UnitY();
		constexpr static Vector4 UnitZ();
		constexpr static Vector4 UnitW();
		constexpr static Vector4 One();

		float Length() const;
		constexpr float LengthSquared() const;

		constexpr static float Dot(const Vector4& a, const Vector4 &b);
		constexpr float Dot(const Vector4& v) const;

		constexpr static Vector4 Hadamard(const Vector4& a, const Vector4& b);
		constexpr Vector4& Hadamard(const Vector4& v);

		constexpr Vector4 operator+(const Vector4& v) const;
		constexpr Vector4& operator+=(const Vector4& v);

		constexpr Vector4& operator-();
		constexpr Vector4 operator-() const;

		constexpr Vector4 operator-(const Vector4& v) const;
		constexpr Vector4& operator -=(const Vector4& v);

		constexpr Vector4 operator *(float scalar) const;
		constexpr Vector4& operator *=(float scalar);

		constexpr Vector4 operator /(float f) const;
		constexpr Vector4& operator /=(float f);

		constexpr Vector4& Transform(const Matrix4x4& m);
		constexpr static Vector4 Transform(const Vector4& v, const Matrix4x4& m);

		constexpr auto operator <=>(const Vector4& v) const = default;
	};

	constexpr Vector4 operator *(float scalar, const Vector4& v);
	constexpr Vector4 operator /(float scalar, const Vector4& v);
}
