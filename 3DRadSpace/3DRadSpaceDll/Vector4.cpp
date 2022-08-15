#include "Vector4.hpp"

float Engine3DRadSpace::Vector4::Lenght() const
{
	return (float)std::sqrt(std::pow<float>(X, 2) + std::pow<float>(Y, 2) + std::pow<float>(Z, 2) + std::pow<float>(W,2));
}

void Engine3DRadSpace::Vector4::Normalize()
{
	float l = this->Lenght();
	this->X /= l;
	this->Y /= l;
	this->Z /= l;
	this->W /= l;
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::Normalize(const Vector4& v)
{
	float l = v.Lenght();
	return Vector4(v.X / l , v.Y / l, v.Z / l,v.W / l);
}

inline Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::operator+=(const Vector4 &v)
{
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
	this->W += v.W;
	return *this;
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::operator-=(const Vector4 &v)
{
	this->X -= v.X;
	this->Y -= v.Y;
	this->Z -= v.Z;
	this->W -= v.W;
	return *this;
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::operator/=(float f)
{
	this->X /= f;
	this->Y /= f;
	this->Z /= f;
	return *this;
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	this->W *= s;
	return *this;
}

float Engine3DRadSpace::Vector4::Dot(const Vector4& v)
{
	return this->X * v.X + this->Y * v.Y + this->Z * v.Z + this->W * v.W;
}

float Engine3DRadSpace::Vector4::Dot(const Vector4& a, const Vector4& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::UnitX()
{
	return Vector4(1,0,0,0);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::UnitY()
{
	return Vector4(0,1,0,0);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::UnitZ()
{
	return Vector4(0,1,0,0);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::UnitW()
{
	return Vector4(0, 0, 0, 1);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::Zero()
{
	return Vector4(0,0,0,0);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::Vector4::One()
{
	return Vector4(1,1,1,1);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::operator+(const Vector4 &a,const Vector4 &b)
{
	return Vector4(a.X + b.X, a.Y + b.Y, a.Z + b.Z,a.W + b.W);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::operator-(const Vector4 &a,const Vector4 &b)
{
	return Vector4(a.X - b.X, a.Y - b.Y, a.Z - b.Z,a.W - b.W);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::operator*(const Vector4 &v,float s)
{
	return Vector4(v.X * s, v.Y * s, v.Z * s,v.W * s);
}

Engine3DRadSpace::Vector4 Engine3DRadSpace::operator/(const Vector4 &v, float f)
{
	return Vector4(v.X / f, v.Y / f, v.Z / f,v.W / f);
}

bool Engine3DRadSpace::operator==(const Vector4& a, const Vector4& b)
{
	return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
}

bool Engine3DRadSpace::operator!=(const Vector4& a, const Vector4& b)
{
	return a.X != b.X && a.Y != b.Y && a.Z != b.Z && a.W != b.W;
}
