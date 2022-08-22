#include "ColorBox.hpp"

WNDPROC ColorBox::StaticProc = nullptr;

LRESULT __stdcall ColorBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_PAINT:
		{
			ColorBox cb = *reinterpret_cast<ColorBox*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint,static_cast<HBRUSH>(cb) );
			EndPaint(hwnd, &ps);
			return 1;
		}
		default:
			return ColorBox::StaticProc(hwnd, msg, wParam, lParam);
	}
}

ColorBox::ColorBox(HINSTANCE hInstance, HWND owner, int x, int y, COLORREF defaultColor, int cx, int cy):
	_colorBrush(CreateSolidBrush(0xFFFFFF)),
	_customColors{ 0xFFFFFF },
	_resultColor(0)
{
	this->_owner = owner;
	this->_hinstance = hInstance;

	this->_hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
		TEXT("Static"),
		TEXT(""),
		SS_NOTIFY | WS_CHILD | WS_VISIBLE,
		x,
		y,
		cx,
		cy,
		owner,
		nullptr,
		hInstance,
		nullptr
	);
	ColorBox::StaticProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(this->_hwnd,GWLP_WNDPROC,reinterpret_cast<LONG_PTR>(ColorBoxProc)));
}

void ColorBox::_setBrush(HBRUSH newColor)
{
	DeleteObject(this->_colorBrush);
	this->_colorBrush = newColor;
}

bool ColorBox::OpenColorDialogBox()
{
	CHOOSECOLOR cc{};
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = this->_owner;
	cc.Flags = CC_FULLOPEN | CC_ANYCOLOR;
	cc.lpCustColors = &this->_customColors[0];

	return ChooseColor(&cc);
}

ColorBox::operator HWND()
{
	return this->_hwnd;
}

ColorBox::operator COLORREF()
{
	return this->_resultColor;
}

ColorBox::operator HBRUSH()
{
	return this->_colorBrush;
}

ColorBox::~ColorBox()
{
	DeleteObject(this->_colorBrush);
}
