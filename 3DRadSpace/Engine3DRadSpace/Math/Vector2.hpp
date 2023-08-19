#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct DLLEXPORT Vector2
	{
		float X, Y;
		Vector2(float x = 0.0f, float y = 0.0f) :X(x), Y(y) {};

		static Vector2 Zero();
		static Vector2 UnitX();
		static Vector2 UnitY();
		static Vector2 One();

		float Length() const;
		float Angle() const;
		
		float Dot(const Vector2 &v) const;
		
		Vector2 Normalize();

		Vector2& operator +=(const Vector2& v);
		Vector2 operator +(const Vector2 &v) const;

		Vector2& operator-();
		Vector2& operator -=(const Vector2& v);
		Vector2 operator -(const Vector2 &v) const;

		float operator*(const Vector2 &v) const;
		Vector2 operator*(float s) const;
		Vector2& operator *=(float s);

		Vector2& operator /=(float f);
		Vector2 operator /(float f) const;

		static Vector2 ConvertFromNormalizedScreenSpaceToClipSpace(const Vector2& norm);

		bool operator ==(const Vector2& v) const = default;
		bool operator !=(const Vector2& v) const = default;
	};
}

Engine3DRadSpace::Math::Vector2 operator*(float s, const Engine3DRadSpace::Math::Vector2& v);
Engine3DRadSpace::Math::Vector2 operator/(float s, const Engine3DRadSpace::Math::Vector2& v);