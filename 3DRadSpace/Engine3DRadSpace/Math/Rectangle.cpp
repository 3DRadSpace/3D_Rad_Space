#include "Rectangle.hpp"
using namespace Engine3DRadSpace::Math;

constexpr Point Rectangle::TopLeft() const
{
    return Point(X, Y);
}

constexpr Point Rectangle::TopRight() const
{
    return Point(X + Width, Y);
}


constexpr Point Rectangle::BottomLeft() const
{
    return Point(X, Y + Height);
}

constexpr Point Rectangle::BottomRight() const
{
    return Point(X + Width, Y + Height);
}

constexpr Point Rectangle::Center() const
{
    return Point((X + Width) / 2, (Y + Height) / 2);
}


// ------------------------------------------------------------------------------ //


constexpr Vector2 RectangleF::TopLeft() const
{
    return Vector2(X, Y);
}

constexpr Vector2 RectangleF::TopRight() const
{
    return Vector2(X + Width, Y);
}


constexpr Vector2 RectangleF::BottomLeft() const
{
    return Vector2(X, Y + Height);
}

constexpr Vector2 RectangleF::BottomRight() const
{
    return Vector2(X + Width, Y + Height);
}

constexpr Vector2 RectangleF::Center() const
{
    return Point((X + Width) / 2.0f, (Y + Height) / 2.0f);
}