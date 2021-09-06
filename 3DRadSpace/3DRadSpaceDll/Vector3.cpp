#include "Vector3.h"

float Vector3::Lenght() const
{
	return (float)std::sqrt(std::pow<float>(X, 2) + std::pow<float>(Y, 2) + std::pow<float>(Z, 2));
}

void Vector3::Normalize()
{
	float l = this->Lenght();
	this->X /= l;
	this->Y /= l;
	this->Z /= l;
}

Vector3 Vector3::Normalize(const Vector3& v)
{
	float l = v.Lenght();
	return Vector3(v.X/l, v.Y/l, v.Z/l);
}

inline Vector3 Vector3::operator+=(const Vector3 &v)
{
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3 &v)
{
	this->X -= v.X;
	this->X -= v.X;
	this->X -= v.X;
	return *this;
}

Vector3 Vector3::operator/=(float f)
{
	this->X /= f;
	this->Y /= f;
	this->Z /= f;
	return *this;
}

Vector3 Vector3::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	return *this;
}

Vector3 Vector3::operator*=(const Matrix& m)
{
	float x = (this->X * m.M11) + (this->Y * m.M21) + (this->Z * m.M31) + m.M41;
	float y = (this->X * m.M12) + (this->Y * m.M22) + (this->Z * m.M32) + m.M42;
	float z = (this->X * m.M13) + (this->Y * m.M23) + (this->Z * m.M33) + m.M43;
	float w = (this->X * m.M13) + (this->Y * m.M23) + (this->Z * m.M33) + m.M43;
	return Vector3(x, y, z);
}

float Vector3::Dot(const Vector3& v)
{
	return this->X * v.X + this->Y * v.Y + this->Z * v.Z;
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

Vector3 Vector3::Cross(const Vector3& v)
{
	float x = this->Y * v.Z - v.Y * this->Z;
	float y = -(this->X * v.Z - v.X * this->Z);
	float z = this->X * v.Y - v.X * this->Y;
	return Vector3(x, y, z);
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	float x = a.Y * b.Z - b.Y * a.Z;
	float y = -(a.X * b.Z - b.X * a.Z);
	float z = a.X * b.Y - b.X * a.Y;
	return Vector3(x, y, z);
}

Vector3 Vector3::UnitX()
{
	return Vector3(1,0,0);
}

Vector3 Vector3::UnitY()
{
	return Vector3(0,1,0);
}

Vector3 Vector3::UnitZ()
{
	return Vector3(0,1,0);
}

Vector3 Vector3::Zero()
{
	return Vector3(0,0,0);
}

Vector3 Vector3::One()
{
	return Vector3(1,1,1);
}

Vector3 operator+(const Vector3 &a,const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

Vector3 operator-(const Vector3 &a,const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

Vector3 operator*(const Vector3 &v,float s)
{
	return Vector3(v.X * s, v.Y * s, v.Z * s);
}

Vector3 operator/(const Vector3 &v, float f)
{
	return Vector3(v.X / f, v.Y / f, v.Z / f);
}

Vector3 Vector3::Transform(const Vector3& v, const Matrix& m)
{
	float x = (v.X * m.M11) + (v.Y * m.M21) + (v.Z * m.M31) + m.M41;
	float y = (v.X * m.M12) + (v.Y * m.M22) + (v.Z * m.M32) + m.M42;
	float z = (v.X * m.M13) + (v.Y * m.M23) + (v.Z * m.M33) + m.M43;
	return Vector3(x, y, z);
}
Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
{
	float x = 2 * (q.Y * v.Z - q.Z * v.Y);
	float y = 2 * (q.Z * v.X - q.X * v.Z);
	float z = 2 * (q.X * v.Y - q.Y * v.X);

	return Vector3(v.X + x * q.W + (q.Y * z - q.Z * y), v.Y + y * q.W + (q.Z * x - q.X * z), v.Z + z * q.W + (q.X * y - q.Y * x));
}

Vector3 DLLEXPORT operator*(const Vector3& v, const Matrix& m)
{
	float x = (v.X * m.M11) + (v.Y * m.M21) + (v.Z * m.M31) + m.M41;
	float y = (v.X * m.M12) + (v.Y * m.M22) + (v.Z * m.M32) + m.M42;
	float z = (v.X * m.M13) + (v.Y * m.M23) + (v.Z * m.M33) + m.M43;
	return Vector3(x, y, z);
}
Vector3 DLLEXPORT operator*(const Vector3& v, const Quaternion& q)
{
	float x = 2 * (q.Y * v.Z - q.Z * v.Y);
	float y = 2 * (q.Z * v.X - q.X * v.Z);
	float z = 2 * (q.X * v.Y - q.Y * v.X);

	return Vector3(v.X + x * q.W + (q.Y * z - q.Z * y), v.Y + y * q.W + (q.Z * x - q.X * z), v.Z + z * q.W + (q.X * y - q.Y * x));
}
