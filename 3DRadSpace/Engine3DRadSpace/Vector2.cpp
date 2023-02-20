#include "Vector2.hpp"

using namespace Engine3DRadSpace::Math;

float Vector2::Length() const
{
    return sqrtf(X*X + Y*Y);
}

float Vector2::Angle() const
{
    return atan2(Y, X);
}

float Vector2::Dot(const Vector2 &v) const
{ 
    return this->X * v.X + this->Y * v.Y;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
    this->X += v.X;
    this->Y += v.Y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& v)
{
    return Vector2(this->X + v.X, this->Y + v.Y);
}

Vector2& Vector2::operator-()
{
    this->X *= -1;
    this->Y *= -1;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
    this->X += v.X;
    this->Y += v.Y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& v)
{
    return Vector2(this->X + v.X, this->Y + v.Y);
}

float Vector2::operator*(const Vector2& v)
{
    return this->X * v.X + this->Y * v.Y;
}

Vector2 Vector2::operator*(float s)
{
    return Vector2(this->X * s, this->Y * s);
}

Vector2& Vector2::operator*=(float s)
{
    this->X *= s;
    this->Y *= s;
    return *this;
}

Vector2 operator*(float s, const Vector2& v)
{
    return Vector2(s * v.X, s * v.Y);
}