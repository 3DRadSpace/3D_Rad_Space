#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Matrix3x3;
	struct DLLEXPORT Vector2
	{
		float X, Y;
		constexpr Vector2(float x = 0.0f, float y = 0.0f) :X(x), Y(y) {};

		constexpr static Vector2 Zero();
		constexpr static Vector2 UnitX();
		constexpr static Vector2 UnitY();
		constexpr static Vector2 One();

		float Length() const;
		float Angle() const;
		
		constexpr float Dot(const Vector2 &v) const;
		constexpr static float Dot(const Vector2& a, const Vector2& b);
		
		Vector2 Normalize();

		constexpr Vector2& operator +=(const Vector2& v);
		constexpr Vector2 operator +(const Vector2 &v) const;

		constexpr Vector2& operator-();
		constexpr Vector2 operator-() const;

		constexpr Vector2& operator -=(const Vector2& v);
		constexpr Vector2 operator -(const Vector2 &v) const;

		constexpr float operator*(const Vector2 &v) const;
		constexpr Vector2 operator*(float s) const;
		constexpr Vector2& operator *=(float s);

		constexpr Vector2& operator /=(float f);
		constexpr Vector2 operator /(float f) const;

		constexpr static Vector2 ConvertFromNormalizedScreenSpaceToClipSpace(const Vector2& norm);
		constexpr static Vector2 ConvertFromScreenCoordsToClipSpace(const Vector2& point, const Vector2& resolution);

		Vector2& RotateBy(float theta);
		static Vector2 Rotate(const Vector2 &v, float theta);

		constexpr Vector2& Hadamard(const Vector2& v);
		constexpr static Vector2 Hadamard(const Vector2& a, const Vector2& b);

		constexpr Vector2& Transform(const Matrix3x3& m);
		constexpr static Vector2 Transform(const Vector2& v, const Matrix3x3& m);
	};

	constexpr Vector2 DLLEXPORT operator*(float s, const Vector2& v);
	constexpr Vector2 DLLEXPORT operator/(float s, const Vector2& v);
}