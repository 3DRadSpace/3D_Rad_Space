#include "Point.h"

Point Point::Zero()
{
    return Point(0,0);
}

Point Point::One()
{
    return Point(1,1);
}

Point Point::operator+=(const Point &p)
{
    return Point(this->X+p.X,this->Y+p.Y);
}

Point Point::operator-=(const Point& p)
{
    return Point(this->X - p.X,this->Y - p.Y);
}

Point Point::operator*=(const Point& p)
{
    return Point(this->X * p.X, this->Y * p.Y);
}

Point Point::operator/=(const Point& p)
{
    return Point(this->X / p.X , this->Y / p.Y);
}

Point operator+(const Point& a, const Point& b)
{
    return Point(a.X+b.X, a.Y+b.Y);
}

Point operator-(const Point& a, const Point& b)
{
    return Point(a.X - b.X, a.Y - b.Y);
}

Point operator*(const Point& a, const Point& b)
{
    return Point(a.X * b.X, a.Y * b.Y);
}

Point operator/(const Point& a, const Point& b)
{
    return Point(a.X / b.X, a.Y / b.Y);
}

Point operator*(const Point& p, float s)
{
    return Point(p.X * s, p.Y*s);
}
