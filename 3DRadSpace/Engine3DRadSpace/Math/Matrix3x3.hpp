#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector2;
	struct DLLEXPORT Matrix3x3
	{
		float M11, M12, M13;
		float M21, M22, M23;
		float M31, M32, M33;

		constexpr explicit Matrix3x3(	float m11 = 1, float m12 = 0, float m13 = 0,
							float m21 = 0, float m22 = 1, float m23 = 0,
							float m31 = 0, float m32 = 0, float m33 = 1);

		constexpr explicit Matrix3x3(float m[9]);

		static Matrix3x3 CreateTranslation(const Vector2 &t);
		static Matrix3x3 CreateScale(const Vector2 &s);
		static Matrix3x3 CreateRotation(float theta);
		static Matrix3x3 Create2DSkewing(const Vector2& skewing);

		constexpr float Trace() const;
		constexpr float Determinant() const;

		constexpr float& operator[](unsigned index);

		constexpr Matrix3x3& Hadamard(const Matrix3x3& m);
		constexpr static Matrix3x3 Hadamard(const Matrix3x3& a, const Matrix3x3& b);

		constexpr Matrix3x3 operator+(const Matrix3x3& m) const;
		constexpr Matrix3x3& operator+=(const Matrix3x3& m);

		constexpr Matrix3x3& operator-();
		constexpr Matrix3x3 operator-(const Matrix3x3& m) const;
		constexpr Matrix3x3& operator-=(const Matrix3x3& m);

		constexpr Matrix3x3 operator*(const Matrix3x3& m) const;
		constexpr Matrix3x3& operator*=(const Matrix3x3& m);

		constexpr Matrix3x3 operator*(float s) const;
		constexpr Matrix3x3& operator*=(float s);

		constexpr Matrix3x3 operator/(float s) const;
		constexpr Matrix3x3& operator/=(float s);
	};

	constexpr Matrix3x3 operator *(float s, const Matrix3x3& m);
	constexpr Matrix3x3 operator /(float s, const Matrix3x3& m);
}