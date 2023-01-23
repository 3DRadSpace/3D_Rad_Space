#include "Mouse.hpp"

void Engine3DRadSpace::Input::Mouse::_setLeftBtn(bool state)
{
    _leftButton = state;
}

void Engine3DRadSpace::Input::Mouse::_setRightBtn(bool state)
{
    _rightButton = state;
}

void Engine3DRadSpace::Input::Mouse::_setPos(const Math::Point& p)
{
    _position = p;
}

void Engine3DRadSpace::Input::Mouse::_setScrollWheel(float wheel)
{
    _scrollWheel = wheel;
}

bool Engine3DRadSpace::Input::Mouse::LeftButton()
{
    return _leftButton;
}

bool Engine3DRadSpace::Input::Mouse::MiddleButton()
{
    return _middleButton;
}

bool Engine3DRadSpace::Input::Mouse::RightButton()
{
    return _rightButton;
}

Engine3DRadSpace::Math::Point Engine3DRadSpace::Input::Mouse::Position()
{
    return _position;
}

float Engine3DRadSpace::Input::Mouse::ScrollWheel()
{
    return _scrollWheel;
}
