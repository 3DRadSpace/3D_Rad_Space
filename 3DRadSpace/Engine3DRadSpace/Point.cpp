#include "Point.hpp"

using namespace Engine3DRadSpace::Math;

Point Point::operator+=(const Point& p)
{
    this->X += p.X;
    this->Y += p.Y;
    return *this;
}

Point Point::operator+(const Point& p)
{
    return Point(this->X + p.X, this->Y + p.Y);
}

Point Point::operator-=(const Point& p)
{
    this->X -= p.X;
    this->Y -= p.Y;
    return *this;
}

Point Point::operator-(const Point& p)
{
    return Point(this->X + p.X, this->Y + p.Y);
}

Point Point::operator-()
{
    this->X *= -1;
    this->Y *= -1;
    return *this;
}

Point Point::operator*=(float s)
{
    this->X *= s;
    this->Y *= s;
    return *this;
}

Point Point::operator*(float s)
{
    return Point(int(this->X * s ),int(this->Y * s));
}

Point Point::operator/=(float s)
{
    this->X /= s;
    this->Y /= s;
    return *this;
}

Point Point::operator/(float s)
{
    return Point(int(this->X / s), int(this->Y / s));
}

Point operator*(float s, const Point& p)
{
    return Point(int(s * p.X), int(s * p.Y));
}

Point operator/(float s, const Point& p)
{
    return Point(int(s / p.X), int(s / p.Y));
}
