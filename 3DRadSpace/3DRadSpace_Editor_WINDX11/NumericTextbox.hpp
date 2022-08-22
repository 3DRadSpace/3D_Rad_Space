#pragma once
#include "Libs.hpp"

class NumericTextbox
{
	HWND _hwnd = nullptr;
public:
	static WNDPROC _editProc;

	NumericTextbox(HWND owner, HINSTANCE hInstance, int x, int y, int cx, int cy, const char* defValue);
	NumericTextbox(NumericTextbox&&) = delete;
	
	operator HWND();
};

