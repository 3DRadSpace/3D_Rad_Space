#include "Point.hpp"

Engine3DRadSpace::Point Engine3DRadSpace::Point::Zero()
{
    return Point(0,0);
}

Engine3DRadSpace::Point Engine3DRadSpace::Point::One()
{
    return Point(1,1);
}

Engine3DRadSpace::Point Engine3DRadSpace::Point::operator+=(const Point &p)
{
    this->X += p.X;
    this->Y += p.Y;
    return *this;
}

Engine3DRadSpace::Point Engine3DRadSpace::Point::operator-=(const Point& p)
{
    this->X -= p.X;
    this->Y -= p.Y;
    return *this;
}

Engine3DRadSpace::Point Engine3DRadSpace::Point::operator*=(const Point& p)
{
    this->X *= p.X;
    this->Y *= p.Y;
    return *this;
}

Engine3DRadSpace::Point Engine3DRadSpace::Point::operator/=(const Point& p)
{
    this->X /= p.X;
    this->Y /= p.Y;
    return *this;
}

Engine3DRadSpace::Point Engine3DRadSpace::operator+(const Point& a, const Point& b)
{
    return Point(a.X+b.X, a.Y+b.Y);
}

Engine3DRadSpace::Point Engine3DRadSpace::operator-(const Point& a, const Point& b)
{
    return Point(a.X - b.X, a.Y - b.Y);
}

Engine3DRadSpace::Point Engine3DRadSpace::operator*(const Point& a, const Point& b)
{
    return Point(a.X * b.X, a.Y * b.Y);
}

Engine3DRadSpace::Point Engine3DRadSpace::operator/(const Point& a, const Point& b)
{
    return Point(a.X / b.X, a.Y / b.Y);
}

Engine3DRadSpace::Point Engine3DRadSpace::operator*(float s,const Point& p)
{
    return Point(static_cast<int>(p.X * s),static_cast<int>(p.Y*s));
}
