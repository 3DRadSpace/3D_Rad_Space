#pragma once
#include "Libs.hpp"

class ISubclassedControl
{
protected:
	HWND _hwnd = nullptr;
	HWND _owner = nullptr;
	HINSTANCE _hinstance = nullptr;
public:
	virtual operator HWND() = 0;
	virtual ~ISubclassedControl();
};

