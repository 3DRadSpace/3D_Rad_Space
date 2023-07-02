#include "NumericTextbox.hpp"
#include <exception>

WNDPROC NumericTextbox::editProc = nullptr;

bool allowedFloatCharacter(char c)
{
	return (c >= '0' && c <= '9') ||
		c == '-' ||
		c == '.' ||
		c == ',' ||
		c == VK_RETURN ||
		c == VK_BACK ||
		c == VK_ESCAPE ||
		c == VK_DELETE ||
		c == VK_CONTROL ||
		c == 0x01 ||
		c == 0x03 ||
		c == 0x16 ||
		c == 0x18;
}

LRESULT WINAPI NumericTextBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CHAR:
		{
			char chr = (char)wParam;

			if (allowedFloatCharacter(chr))
			{
				return NumericTextbox::editProc(hwnd, msg, wParam, lParam);
			}
			else return MessageBeep(MB_ICONINFORMATION);
		}
		case WM_PASTE:
		{
			BOOL r = OpenClipboard(hwnd);
			if (!r) return 0;

			HANDLE clipboardData = GetClipboardData(CF_OEMTEXT);
			if (clipboardData == nullptr) return 0;

			char* clipboardString = static_cast<char*>(GlobalLock(clipboardData));
			if (clipboardString == nullptr) return 0;

			for (size_t i = 0; i < strlen(clipboardString); i++)
			{
				SendMessageA(hwnd, WM_CHAR, clipboardString[i], 0);
			}
			r = GlobalUnlock(clipboardData);
			if (!r) return 0;

			r = CloseClipboard();
			if (!r) return 0;

			return 1;
		}
		default:
			return NumericTextbox::editProc(hwnd, msg, wParam, lParam);
	}
}

NumericTextbox::NumericTextbox(HWND owner, HINSTANCE hInstance, int x, int y, int cx, int cy, const char* value):
	IControl(owner, hInstance)
{
	window = CreateWindowExA(
		0,
		"Edit",
		value,
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		x, y, cx, cy,
		owner,
		nullptr,
		hInstance,
		nullptr
	);
	if (window == nullptr) throw std::exception("Failed to create a edit/textbox control for a NumericTextbox!");

	editProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NumericTextBoxProc)));
}

NumericTextbox::operator HWND() const
{
	return this->window;
}
