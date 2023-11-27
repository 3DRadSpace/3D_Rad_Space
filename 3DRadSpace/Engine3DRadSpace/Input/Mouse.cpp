#include "Mouse.hpp"
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

Mouse::Mouse() :
	_leftButton(ButtonState::Released),
	_middleButton(ButtonState::Released),
	_rightButton(ButtonState::Released),
	_position(),
	_scrollWheel(0)
{
};

ButtonState Mouse::LeftButton()
{
    return _leftButton;
}

ButtonState Mouse::MiddleButton()
{
    return _middleButton;
}

ButtonState Mouse::RightButton()
{
    return _rightButton;
}

Point Mouse::Position()
{
    return _position;
}

float Mouse::ScrollWheel()
{
    return _scrollWheel;
}
