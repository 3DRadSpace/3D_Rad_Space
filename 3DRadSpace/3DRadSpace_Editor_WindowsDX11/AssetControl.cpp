#include "AssetControl.hpp"

AssetControl::AssetControl(HWND owner, HINSTANCE hInstance, int x, int y):
    IControl(owner, hInstance)
{
	HDC hdc = GetDC(owner);

	SIZE txtLen;
	GetTextExtentPoint32A(hdc, "Path", 4, &txtLen);

	_label = CreateWindowExA(
		0,
		"STATIC",
		"Path",
		WS_VISIBLE | WS_CHILD,
		x,
		y,
		txtLen.cx + 2,
		txtLen.cy + 2,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_cy = txtLen.cy;

	_textBox = CreateWindowExA(
		0,
		"EDIT",
		"",
		ES_AUTOHSCROLL | ES_LEFT | WS_CHILD | WS_VISIBLE,
		x + txtLen.cx + 5,
		y,
		100,
		txtLen.cy + 2,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	GetTextExtentPoint32A(hdc, "Browse...", 9, &txtLen);
	_button = CreateWindowExA(
		0,
		"Button",
		"Browse...",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		x + 110,
		y,
		txtLen.cx + 10,
		25,
		window,
		nullptr,
		hInstance,
		nullptr
	);
}

HWND AssetControl::GetTextbox()
{
    return _textBox;
}

HWND AssetControl::GetBrowseButton()
{
    return _button;
}
