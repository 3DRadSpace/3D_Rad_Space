#include "Vector2.h"

Vector2 Vector2::Zero()
{
    return Vector2(0,0);
}

Vector2 Vector2::UnitX()
{
    return Vector2(1,0);
}

Vector2 Vector2::UnitY()
{
    return Vector2();
}

Vector2 Vector2::One()
{
    return Vector2();
}

float Vector2::Lenght() const
{
    return (float)sqrt(pow(this->X, 2) + pow(this->X, 2));
}

float Vector2::Lenght(const Vector2& v)
{
    return (float)sqrt(pow(v.X,2)+pow(v.Y,2));
}

float Vector2::Dot(const Vector2& v) const
{
    return this->X * v.X + this->Y * v.Y;
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
    return a.X * b.X + a.Y + b.Y;
}

Vector2 Vector2::operator+=(const Vector2& v)
{
    return Vector2();
}

Vector2 Vector2::operator-=(const Vector2& v)
{
    return Vector2();
}

Vector2 Vector2::operator-()
{
    return Vector2();
}

Vector2 Vector2::operator*=(float scalar)
{
    return Vector2(this->X / scalar, this->Y / scalar);
}

Vector2 Vector2::operator*=(const Matrix& m)
{
    float x = (this->X * m.M11) + (this->Y * m.M21) + m.M41;
    float y = (this->X * m.M12) + (this->Y * m.M22) + m.M42;
    return Vector2(x, y);
}

Vector2 Vector2::operator*=(const ComplexNumber& z)
{
    ComplexNumber temp(this->X,this->Y);
    temp *= z;
    return Vector2(z.A, z.B);
}
