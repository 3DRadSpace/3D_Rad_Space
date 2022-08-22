#pragma once
#include "ISubclassedControl.hpp"

class ColorBox : public ISubclassedControl
{
	HBRUSH _colorBrush;
	std::array<COLORREF, 16> _customColors;
	COLORREF _resultColor;

	void _setBrush(HBRUSH newColor);
public:
	static WNDPROC StaticProc;
	ColorBox(HINSTANCE hInstance, HWND owner, int x, int y, COLORREF defaultColor = 0xFFFFFF, int cx = 20, int cy = 20);

	bool OpenColorDialogBox();

	operator HWND() final;
	operator COLORREF();
	operator HBRUSH();

	~ColorBox();
};

