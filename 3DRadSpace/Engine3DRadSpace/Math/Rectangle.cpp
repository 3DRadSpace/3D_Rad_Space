#include "Rectangle.hpp"
using namespace Engine3DRadSpace::Math;

Point Rectangle::TopLeft() const
{
    return Point(X, Y);
}

Point Rectangle::TopRight() const
{
    return Point(X + Width, Y);
}


Point Rectangle::BottomLeft() const
{
    return Point(X, Y + Height);
}

Point Rectangle::BottomRight() const
{
    return Point(X + Width, Y + Height);
}


// ------------------------------------------------------------------------------ //


Vector2 RectangleF::TopLeft() const
{
    return Vector2(X, Y + Height);
}

Vector2 RectangleF::TopRight() const
{
    return Vector2(X + Width, Y + Height);
}


Vector2 RectangleF::BottomLeft() const
{
    return Vector2(X, Y);
}

Vector2 RectangleF::BottomRight() const
{
    return Vector2(X + Width, Y);
}