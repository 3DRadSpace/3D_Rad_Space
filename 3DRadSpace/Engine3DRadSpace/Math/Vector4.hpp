#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT Vector4
	{
		float X, Y, Z, W;

		explicit constexpr Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : X(x), Y(y), Z(z), W(w) {};
		explicit constexpr Vector4(Vector3 v) : X(v.X), Y(v.Y), Z(v.Z), W(1) {};
		explicit constexpr Vector4(std::initializer_list<float> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0.0f),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0.0f),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0.0f),
			W(lst.size() > 3 ? *(lst.begin() + 3) : 0.0f)
		{
		};

		static Vector4 Zero();
		static Vector4 UnitX();
		static Vector4 UnitY();
		static Vector4 UnitZ();
		static Vector4 UnitW();
		static Vector4 One();

		float Length() const;
		float LengthSquared() const;

		Vector4& Normalize();

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

	Vector4 E3DRSP_MATH_EXPORT operator *(float scalar, const Vector4& v);
	Vector4 E3DRSP_MATH_EXPORT operator /(float scalar, const Vector4& v);
}
