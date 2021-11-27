#include "Vector3.hpp"

float Engine3DRadSpace::Vector3::Lenght() const
{
	return (float)std::sqrt(std::pow<float>(X, 2) + std::pow<float>(Y, 2) + std::pow<float>(Z, 2));
}

void Engine3DRadSpace::Vector3::Normalize()
{
	float l = this->Lenght();
	this->X /= l;
	this->Y /= l;
	this->Z /= l;
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::Normalize(const Vector3& v)
{
	float l = v.Lenght();
	return Vector3(v.X/l, v.Y/l, v.Z/l);
}

inline Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::operator+=(const Vector3 &v)
{
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
	return *this;
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::operator-=(const Vector3 &v)
{
	this->X -= v.X;
	this->X -= v.X;
	this->X -= v.X;
	return *this;
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::operator/=(float f)
{
	this->X /= f;
	this->Y /= f;
	this->Z /= f;
	return *this;
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	return *this;
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::operator*=(const Matrix& m)
{
	float x = (this->X * m.M11) + (this->Y * m.M21) + (this->Z * m.M31) + m.M41;
	float y = (this->X * m.M12) + (this->Y * m.M22) + (this->Z * m.M32) + m.M42;
	float z = (this->X * m.M13) + (this->Y * m.M23) + (this->Z * m.M33) + m.M43;
	return Vector3(x, y, z);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::operator-()
{
	return Vector3(-this->X,-this->Y,-this->Z);
}

float Engine3DRadSpace::Vector3::Dot(const Vector3& v)
{
	return this->X * v.X + this->Y * v.Y + this->Z * v.Z;
}

float Engine3DRadSpace::Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::Cross(const Vector3& v)
{
	float x = this->Y * v.Z - v.Y * this->Z;
	float y = -(this->X * v.Z - v.X * this->Z);
	float z = this->X * v.Y - v.X * this->Y;
	return Vector3(x, y, z);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::Cross(const Vector3& a, const Vector3& b)
{
	float x = a.Y * b.Z - b.Y * a.Z;
	float y = -(a.X * b.Z - b.X * a.Z);
	float z = a.X * b.Y - b.X * a.Y;
	return Vector3(x, y, z);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::UnitX()
{
	return Vector3(1,0,0);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::UnitY()
{
	return Vector3(0,1,0);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::UnitZ()
{
	return Vector3(0,0,1);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::Zero()
{
	return Vector3(0,0,0);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::One()
{
	return Vector3(1,1,1);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::operator+(const Vector3 &a,const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::operator-(const Vector3 &a,const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::operator*(float s,const Vector3 &v)
{
	return Vector3(v.X * s, v.Y * s, v.Z * s);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::operator/(float f,const Vector3 &v)
{
	return Vector3(v.X / f, v.Y / f, v.Z / f);
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::Transform(const Vector3& v, const Matrix& m)
{
	float x = (v.X * m.M11) + (v.Y * m.M21) + (v.Z * m.M31) + m.M41;
	float y = (v.X * m.M12) + (v.Y * m.M22) + (v.Z * m.M32) + m.M42;
	float z = (v.X * m.M13) + (v.Y * m.M23) + (v.Z * m.M33) + m.M43;
	return Vector3(x, y, z);
}
Engine3DRadSpace::Vector3 Engine3DRadSpace::Vector3::Transform(const Vector3& v, const Quaternion& q)
{
	float x = 2 * (q.Y * v.Z - q.Z * v.Y);
	float y = 2 * (q.Z * v.X - q.X * v.Z);
	float z = 2 * (q.X * v.Y - q.Y * v.X);

	return Vector3(v.X + x * q.W + (q.Y * z - q.Z * y), v.Y + y * q.W + (q.Z * x - q.X * z), v.Z + z * q.W + (q.X * y - q.Y * x));
}

Engine3DRadSpace::Vector3 Engine3DRadSpace::operator*(const Vector3& v, const Matrix& m)
{
	float x = (v.X * m.M11) + (v.Y * m.M21) + (v.Z * m.M31) + m.M41;
	float y = (v.X * m.M12) + (v.Y * m.M22) + (v.Z * m.M32) + m.M42;
	float z = (v.X * m.M13) + (v.Y * m.M23) + (v.Z * m.M33) + m.M43;
	return Vector3(x, y, z);
}
Engine3DRadSpace::Vector3 Engine3DRadSpace::operator*(const Vector3& v, const Quaternion& q)
{
	float x = 2 * (q.Y * v.Z - q.Z * v.Y);
	float y = 2 * (q.Z * v.X - q.X * v.Z);
	float z = 2 * (q.X * v.Y - q.Y * v.X);

	return Vector3(v.X + x * q.W + (q.Y * z - q.Z * y), v.Y + y * q.W + (q.Z * x - q.X * z), v.Z + z * q.W + (q.X * y - q.Y * x));
}
