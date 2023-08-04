#include "AssetControl.hpp"

using namespace Engine3DRadSpace::Content;

AssetControl::AssetControl(HWND owner, HINSTANCE hInstance, int x, int y, ContentManager *content):
    IControl(owner, hInstance),
	_content(content)
{
	HDC hdc = GetDC(owner);

	SIZE txtLen;
	GetTextExtentPoint32A(hdc, "Asset name", 10, &txtLen);

	_cx = x;

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
	_cx += txtLen.cx;

	_textBox = CreateWindowExA(
		0,
		"EDIT",
		"",
		ES_AUTOHSCROLL | ES_LEFT | WS_CHILD | WS_VISIBLE,
		_cx + 5,
		y,
		100,
		txtLen.cy + 2,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_cx += 110;

	GetTextExtentPoint32A(hdc, "Browse...", 9, &txtLen);
	_button = CreateWindowExA(
		0,
		"Button",
		"Browse...",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		_cx + 5,
		y,
		txtLen.cx + 10,
		txtLen.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_cx += txtLen.cx + 15;
}

HWND AssetControl::GetTextbox()
{
    return _textBox;
}

HWND AssetControl::GetBrowseButton()
{
    return _button;
}

int AssetControl::AccX()
{
	return _cx;
}
