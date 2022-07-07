#include "Vector2.hpp"

Engine3DRadSpace::Vector2 Engine3DRadSpace::Vector2::Zero()
{
	return Vector2(0,0);
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::Vector2::UnitX()
{
	return Vector2(1,0);
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::Vector2::UnitY()
{
	return Vector2(0,1);
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::Vector2::One()
{
	return Vector2(1,1);
}

float Engine3DRadSpace::Vector2::Lenght() const
{
	return (float)sqrt(pow(this->X, 2) + pow(this->X, 2));
}

float Engine3DRadSpace::Vector2::Lenght(const Vector2& v)
{
	return (float)sqrt(pow(v.X,2)+pow(v.Y,2));
}

float Engine3DRadSpace::Vector2::Dot(const Vector2& v) const
{
	return this->X * v.X + this->Y * v.Y;
}

float Engine3DRadSpace::Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.X * b.X + a.Y + b.Y;
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::Vector2::operator*=(float scalar)
{
	this->X *= scalar;
	this->Y *= scalar;
	return *this;
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::Vector2::operator*=(const Matrix& m)
{
	this->X = (this->X * m.M11) + (this->Y * m.M21) + m.M41;
	this->Y = (this->X * m.M12) + (this->Y * m.M22) + m.M42;
	return *this;
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::Vector2::operator*=(const std::complex<float>& z)
{
	std::complex a(this->X, this->Y);
	a *= z;
	this->X = a.real();
	this->Y = a.imag();
	return *this;
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::operator+(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X+ b.X , a.Y + b.Y);
}

Engine3DRadSpace::Vector2 Engine3DRadSpace::operator-(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X - b.X, a.Y - b.Y);
}
bool DLLEXPORT Engine3DRadSpace::operator==(const Vector2& a, const Vector2& b)
{
	return a.X == b.X && a.Y == b.Y;
}
bool DLLEXPORT Engine3DRadSpace::operator!=(const Vector2& a, const Vector2& b)
{
	return a.X != b.X && a.Y != b.Y;
}