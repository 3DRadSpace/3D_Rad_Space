#include "Point.hpp"

using namespace Engine3DRadSpace::Math;

Point Point::operator+=(const Point& p)
{
    this->X += p.X;
    this->Y += p.Y;
    return *this;
}

Point Point::operator+(const Point& p) const
{
    return Point(this->X + p.X, this->Y + p.Y);
}

Point Point::operator-=(const Point& p)
{
    this->X -= p.X;
    this->Y -= p.Y;
    return *this;
}

Point Point::operator-(const Point& p) const
{
    return Point(this->X - p.X, this->Y - p.Y);
}

Point Point::operator-()
{
    this->X *= -1;
    this->Y *= -1;
    return *this;
}

#pragma warning(push)
#pragma warning(disable : 4244)
Point Point::operator*=(float s)
{
    this->X *= s;
    this->Y *= s;
    return *this;
}

Point Point::operator*(float s) const
{
    return Point(int(this->X * s ),int(this->Y * s));
}

Point Point::operator/=(float s)
{
    this->X /= s;
    this->Y /= s;
    return *this;
}
#pragma warning(pop)

Point Point::operator/(float s) const
{
    return Point(int(this->X / s), int(this->Y / s));
}

Engine3DRadSpace::Math::Point::operator Engine3DRadSpace::Math::Vector2() const
{
    return Vector2(float(X), float(Y));
}

Point operator*(float s, const Point& p)
{
    return Point(int(s * p.X), int(s * p.Y));
}

Point operator/(float s, const Point& p)
{
    return Point(int(s / p.X), int(s / p.Y));
}