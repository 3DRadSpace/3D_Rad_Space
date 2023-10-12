#pragma once
#include <Windows.h>

class IControl
{
protected:
	HWND window;
	HWND owner;
	HINSTANCE instance;
public:
	IControl(HWND hwnd, HINSTANCE hInstance);

	virtual void HandleClick(HWND clickedWindow) = 0;

	virtual ~IControl() = default;
};
