#include "ColorBox.hpp"
#include <stdexcept>

WNDPROC ColorBox::staticProc = nullptr;

LRESULT WINAPI ColorBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_PAINT:
		{
			ColorBox* cb = reinterpret_cast<ColorBox*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));

			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, cb->brush);
			EndPaint(hwnd, &ps);
			return 1;
		}
		default:
			return ColorBox::staticProc(hwnd, msg, wParam, lParam);
	}
}

ColorBox::ColorBox(HWND owner, HINSTANCE hInstance, int x, int y, int cx, int cy, Engine3DRadSpace::Color color) :
	IControl(owner, hInstance),
	customColors{ 0xFFFFFF }
{
	SetColor(color);

	window = CreateWindowExA(
		WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
		"Static",
		"",
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

	SetWindowLongPtrA(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	staticProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(ColorBoxProc)));
}

void ColorBox::SetColor()
{
	CHOOSECOLORA cc{};
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = owner;
	cc.Flags = CC_FULLOPEN | CC_ANYCOLOR;
	cc.lpCustColors = &customColors[0];

	BOOL r = ChooseColorA(&cc);
	if (r)
	{
		SetColor(Engine3DRadSpace::Color(
			GetRValue(cc.rgbResult),
			GetGValue(cc.rgbResult),
			GetBValue(cc.rgbResult)
		));
	}
}

void ColorBox::SetColor(Engine3DRadSpace::Color color)
{
	this->color = color; //store a copy of the color, to avoid using GetObject().

	if(brush) DeleteObject(brush);

#pragma warning(push)
#pragma warning(disable: 4244)
	uint8_t r(255 * color.R);
	uint8_t g(255 * color.G);
	uint8_t b(255 * color.B);
#pragma warning(pop)

	brush = CreateSolidBrush(RGB(r, g, b));
	if (brush == nullptr) throw std::bad_alloc();
}

Engine3DRadSpace::Color ColorBox::GetColor()
{
	return color;
}

ColorBox::~ColorBox()
{
	if (brush != nullptr)
	{
		DeleteObject(brush);
		brush = nullptr;
	}
}
