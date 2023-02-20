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
    return _position;
}

float Engine3DRadSpace::Input::Mouse::ScrollWheel()
{
    return _scrollWheel;
}

void Engine3DRadSpace::Input::Mouse::SetPosition(const Math::Point& p)
{
#ifdef _DX11
    BOOL r = SetCursorPos(p.X, p.Y);
    if (r == 0)
    {
        throw std::system_error(std::error_code(GetLastError(),std::system_category()),"Failed to set the mouse position!");
    }
#endif
}
