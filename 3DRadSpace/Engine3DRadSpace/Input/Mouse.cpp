#include "Mouse.hpp"

bool Engine3DRadSpace::Input::Mouse::LeftButton()
{
    return leftButton;
}

bool Engine3DRadSpace::Input::Mouse::MiddleButton()
{
    return middleButton;
}

bool Engine3DRadSpace::Input::Mouse::RightButton()
{
    return rightButton;
}

Engine3DRadSpace::Math::Point Engine3DRadSpace::Input::Mouse::Position()
{
    return position;
}

float Engine3DRadSpace::Input::Mouse::ScrollWheel()
{
    return scrollWheel;
}
