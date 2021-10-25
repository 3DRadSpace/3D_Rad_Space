#pragma once
#include <cmath>
#include "Globals.h"
#include "Matrix.h"
#include "Quaternion.h"

struct DLLEXPORT Matrix;

struct DLLEXPORT Vector3
{
	float X, Y, Z;

	Vector3() = default;
	Vector3(float x,float y,float z): X(x),Y(y),Z(z) {}

	float Lenght() const;
	void Normalize();
	static Vector3 Normalize(const Vector3& v);

	Vector3 operator +=(const Vector3 &v);
	Vector3 operator -=(const Vector3 &v);
	Vector3 operator /=(float f);
	Vector3 operator *=(float s);

	Vector3 operator *=(const Matrix& m);

	Vector3 operator -();

	float Dot(const Vector3 &v);
	static float Dot(const Vector3& a,const Vector3& b);

	Vector3 Cross(const Vector3& v);
	static Vector3 Cross(const Vector3& a, const Vector3& b);

	static Vector3 UnitX();
	static Vector3 UnitY();
	static Vector3 UnitZ();
	static Vector3 Zero();
	static Vector3 One();
	static Vector3 Transform(const Vector3& v, const Matrix& m);
	static Vector3 Transform(const Vector3& v, const Quaternion& q);

};

Vector3 DLLEXPORT operator +(const Vector3 &a, const Vector3 &b);
Vector3 DLLEXPORT operator -(const Vector3 &a, const Vector3 &b);
Vector3 DLLEXPORT operator *(const Vector3 &v, float s);
Vector3 DLLEXPORT operator /(const Vector3 &v, float f);

Vector3 DLLEXPORT operator *(const Vector3 &v,const Matrix &m);
Vector3 DLLEXPORT operator *(const Vector3 &v,const Quaternion &q);