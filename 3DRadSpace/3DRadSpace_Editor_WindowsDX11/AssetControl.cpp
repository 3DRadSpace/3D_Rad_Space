#include "AssetControl.hpp"

AssetControl::AssetControl(HWND owner, HINSTANCE hInstance, int x, int y):
    IControl(owner, hInstance)
{
	HDC hdc = GetDC(owner);

	SIZE txtLen;
	GetTextExtentPoint32A(hdc, "Asset name", 10, &txtLen);

	int accX = x;

	_label = CreateWindowExA(
		0,
		"STATIC",
		"Asset name",
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
	accX += txtLen.cx;

	_textBox = CreateWindowExA(
		0,
		"EDIT",
		"",
		ES_AUTOHSCROLL | ES_LEFT | WS_CHILD | WS_VISIBLE,
		accX + 5,
		y,
		100,
		txtLen.cy + 2,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	accX += 110;

	GetTextExtentPoint32A(hdc, "Browse...", 9, &txtLen);
	_button = CreateWindowExA(
		0,
		"Button",
		"Browse...",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		accX + 5,
		y,
		txtLen.cx + 10,
		txtLen.cy + 5,
		owner,
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
