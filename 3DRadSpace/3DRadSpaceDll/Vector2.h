#pragma once
#include "Globals.h"
#include "Matrix.h"
#include "ComplexNumber.h"

struct DLLEXPORT Vector2
{
	float X, Y;
	Vector2() : X(0), Y(0) {};
	Vector2(float x, float y) : X(x), Y(y) {};

	static Vector2 Zero();
	static Vector2 UnitX();
	static Vector2 UnitY();
	static Vector2 One();

	float Lenght() const;
	static float Lenght(const Vector2& v);

	float Dot(const Vector2 &v) const;
	static float Dot(const Vector2& a,const Vector2 &b);

	Vector2 operator +=(const Vector2& v);
	Vector2 operator -=(const Vector2& v);
	Vector2 operator -();

	Vector2 operator *=(float scalar);
	Vector2 operator *=(const Matrix& m);
	Vector2 operator *=(const ComplexNumber& z);

};

