#include "Vector2.hpp"

using namespace Engine3DRadSpace::Math;

Vector2 Engine3DRadSpace::Math::Vector2::Zero()
{
    return Vector2(0,0);
}

Vector2 Engine3DRadSpace::Math::Vector2::UnitX()
{
    return Vector2(1,0);
}

Vector2 Engine3DRadSpace::Math::Vector2::UnitY()
{
    return Vector2(0,1);
}

Vector2 Engine3DRadSpace::Math::Vector2::One()
{
    return Vector2(1,1);
}

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

Vector2 Engine3DRadSpace::Math::Vector2::Normalize()
{
    float l = Length();
    X /= l;
    Y /= l;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
    this->X += v.X;
    this->Y += v.Y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& v) const
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
    this->X -= v.X;
    this->Y -= v.Y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const
{
    return Vector2(this->X - v.X, this->Y - v.Y);
}

float Vector2::operator*(const Vector2& v) const
{
    return this->X * v.X + this->Y * v.Y;
}

Vector2 Vector2::operator*(float s) const
{
    return Vector2(this->X * s, this->Y * s);
}

Vector2& Vector2::operator*=(float s)
{
    this->X *= s;
    this->Y *= s;
    return *this;
}

Vector2 &Engine3DRadSpace::Math::Vector2::operator/=(float f)
{
    this->X /= f;
    this->Y /= f;
    return *this;
}

Vector2 Engine3DRadSpace::Math::Vector2::operator/(float f) const
{
    return Vector2(X / f, Y / f);
}

Vector2 Engine3DRadSpace::Math::Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(const Vector2 &norm)
{
    return Vector2(
        norm.X * 2 - 1,
        (norm.Y) * 2 + 0.5
    );
 }

Vector2 operator*(float s, const Vector2& v)
{
    return Vector2(s * v.X, s * v.Y);
}