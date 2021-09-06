#pragma once
#include <cmath>
#include "Globals.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector3.h"

struct DLLEXPORT Matrix;

struct DLLEXPORT Vector4
{
	float X, Y, Z, W;

	Vector4() = default;
	Vector4(float x,float y,float z,float w): X(x),Y(y),Z(z),W(w) {}
	Vector4(const Vector3& v, float w) : X(v.X), Y(v.Y), Z(v.Z), W(w) {};

	float Lenght() const;
	void Normalize();
	static Vector4 Normalize(const Vector4& v);

	Vector4 operator +=(const Vector4 &v);
	Vector4 operator -=(const Vector4 &v);
	Vector4 operator /=(float f);
	Vector4 operator *=(float s);

	float Dot(const Vector4 &v);
	static float Dot(const Vector4& a,const Vector4& b);

	static Vector4 UnitX();
	static Vector4 UnitY();
	static Vector4 UnitZ();
	static Vector4 UnitW();
	static Vector4 Zero();
	static Vector4 One();
};
