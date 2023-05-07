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

	operator HWND();
	virtual ~IControl() = default;
};
