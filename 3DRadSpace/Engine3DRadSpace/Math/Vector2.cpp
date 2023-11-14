#include "Vector2.hpp"
#include "Matrix3x3.hpp"

using namespace Engine3DRadSpace::Math;

Vector2 Vector2::Zero()
{
    return { 0,0 };
}

Vector2 Vector2::UnitX()
{
    return { 1,0 };
}

Vector2 Vector2::UnitY()
{
    return { 0,1 };
}

Vector2 Vector2::One()
{
    return { 1,1 };
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
    return X * v.X + Y * v.Y;
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
    return a.X * b.X + a.Y * b.Y;
}

Vector2 Vector2::Normalize()
{
    const float l = Length();
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
    return Vector2
    {
        X + v.X,
        Y + v.Y
    };
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

Vector2 & Vector2::operator/=(float f)
{
    this->X /= f;
    this->Y /= f;
    return *this;
}

Vector2 Vector2::operator/(float f) const
{
    return Vector2(X / f, Y / f);
}

Vector2 Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(const Vector2 &norm)
{
    return Vector2(
        norm.X * 2 - 1,
        -(norm.Y * 2 - 1)
    );
 }

Vector2 Vector2::ConvertFromScreenCoordsToClipSpace(const Vector2& point, const Vector2& resolution)
{
    return ConvertFromNormalizedScreenSpaceToClipSpace(Hadamard(point, 1 / resolution));
}

Vector2 operator*(float s, const Vector2& v)
{
    return Vector2(s * v.X, s * v.Y);
}

Vector2 operator/(float s, const Vector2& v)
{
    return Vector2{ s / v.X, s / v.Y };
}

Vector2& Vector2::RotateBy(float theta)
{
    return *this = Vector2{
        Length() * cosf(Angle() + theta),
        Length() * sinf(Angle() + theta)
    };
}

Vector2 Vector2::Rotate(const Vector2 &v, float theta)
{
    return Vector2
    {
        v.Length() * cosf(v.Angle() + theta),
        v.Length() * sinf(v.Angle() + theta)
    };
}

Vector2& Vector2::Hadamard(const Vector2& v)
{
    X *= v.X;
    Y += v.Y;
    return *this;
}

Vector2 Vector2::Hadamard(const Vector2& a, const Vector2& b)
{
    return Vector2
    {
        a.X * b.X,
        a.Y * b.Y
    };
}

Vector2& Vector2::Transform(const Matrix3x3& m)
{
    X = m.M11 * X + m.M12 * Y + m.M13;
    Y = m.M21 * X + m.M22 * Y + m.M23;

    return *this;
}

Vector2 Vector2::Transform(const Vector2& v, const Matrix3x3& m)
{
    return Vector2{
        v.X * m.M11 + v.Y * m.M12 + m.M13,
        v.X * m.M21 + v.Y * m.M22 + m.M13
    };
}

Vector2 Engine3DRadSpace::Math::operator/(float s, const Vector2& v)
{
    return Vector2{ s / v.X, s / v.Y };
}
