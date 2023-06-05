#include "Mouse.hpp"

Engine3DRadSpace::Input::Mouse::Mouse() :
	_leftButton(false),
	_middleButton(false),
	_rightButton(false),
	_position(),
	_scrollWheel(0)
{
};

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
