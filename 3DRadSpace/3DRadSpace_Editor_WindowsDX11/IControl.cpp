#include "IControl.hpp"

IControl::IControl(HWND hwnd, HINSTANCE HInstance):
	window(nullptr),
	owner(hwnd),
	instance(HInstance)
{
}
