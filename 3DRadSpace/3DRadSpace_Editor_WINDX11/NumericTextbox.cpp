#include "NumericTextbox.hpp"

WNDPROC NumericTextbox::_editProc = nullptr;

bool _isAllowedFloatCharacter(char c)
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

LRESULT __stdcall NumericTextBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CHAR:
		{
			char chr = (char)wParam;

			if(_isAllowedFloatCharacter(chr))
			{
				return NumericTextbox::_editProc(hwnd, msg, wParam, lParam);
			}
			else return MessageBeep(MB_ICONINFORMATION);
		}
		case WM_PASTE:
		{
			BOOL r = OpenClipboard(hwnd);
			if(!r) return 0;

			HANDLE clipboardData = GetClipboardData(CF_OEMTEXT);
			if(clipboardData == nullptr) return 0;

			char* clipboardString = static_cast<char*>(GlobalLock(clipboardData));
			if(clipboardString == nullptr) return 0;

			for(size_t i = 0; i < strlen(clipboardString); i++)
			{
				SendMessage(hwnd, WM_CHAR, clipboardString[i], 0);
			}

			GlobalUnlock(clipboardData);
			CloseClipboard();

			return 1;
		}
		default:
			return NumericTextbox::_editProc(hwnd, msg, wParam, lParam);
	}
}


NumericTextbox::NumericTextbox(HWND owner, HINSTANCE hInstance, int x, int y, int cx, int cy, const char* defValue)
{
	this->_hwnd = CreateWindowExA(
		0,
		"Edit",
		defValue,
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		x, y, cx, cy,
		owner,
		nullptr,
		hInstance,
		nullptr
	);
	if(this->_hwnd == nullptr) throw std::runtime_error(std::string("Failed to create a numeric textbox with default value: ") + defValue);

	_editProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NumericTextBoxProc)));
}

NumericTextbox::operator HWND()
{
	return this->_hwnd;
}