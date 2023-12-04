#include "Point.hpp"

using namespace Engine3DRadSpace::Math;

constexpr Point Point::operator+=(const Point& p)
{
    this->X += p.X;
    this->Y += p.Y;
    return *this;
}

constexpr Point Point::operator+(const Point& p) const
{
    return Point(this->X + p.X, this->Y + p.Y);
}

constexpr Point Point::operator-=(const Point& p)
{
    this->X -= p.X;
    this->Y -= p.Y;
    return *this;
}

constexpr Point Point::operator-(const Point& p) const
{
    return Point(this->X - p.X, this->Y - p.Y);
}

constexpr Point Point::operator-()
{
    this->X *= -1;
    this->Y *= -1;
    return *this;
}

#pragma warning(push)
#pragma warning(disable : 4244)
constexpr Point Point::operator*=(float s)
{
    this->X *= s;
    this->Y *= s;
    return *this;
}

constexpr Point Point::operator*(float s) const
{
    return Point(int(this->X * s ),int(this->Y * s));
}

constexpr Point Point::operator/=(float s)
{
    this->X /= s;
    this->Y /= s;
    return *this;
}
#pragma warning(pop)

constexpr Point Point::operator/(float s) const
{
    return Point(int(this->X / s), int(this->Y / s));
}

constexpr Engine3DRadSpace::Math::Point::operator Engine3DRadSpace::Math::Vector2() const
{
    return Vector2(float(X), float(Y));
}

constexpr Point operator*(float s, const Point& p)
{
    return Point(int(s * p.X), int(s * p.Y));
}

constexpr Point operator/(float s, const Point& p)
{
    return Point(int(s / p.X), int(s / p.Y));
}