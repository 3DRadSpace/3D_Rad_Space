#include "SettingsWindow.hpp"

INT_PTR SettingsWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static SettingsWindow* settingsWindow = nullptr;
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			settingsWindow = reinterpret_cast<SettingsWindow*>(lParam);
			settingsWindow->window = hwnd;
			settingsWindow->_createControls();
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
			EndPaint(hwnd, &ps);
			return 1;
		}
		case WM_CLOSE:
		{
			EndDialog(hwnd, IDCANCEL);
			return 1;
		}
	}
	return 0;
}

HWND SettingsWindow::SettingControl<void>::GetHandle()
{
	return _window;
}

SettingsWindow::SettingControl<bool>::SettingControl(Setting<bool>& t, HWND owner, HINSTANCE hInstance, int py) :
	SettingControlBase(t)
{
	HDC hdc = GetDC(owner);
	SIZE textSize;
	GetTextExtentPoint32A(hdc, t.Name.c_str(), int(t.Name.length()), &textSize);

	_window = CreateWindowExA(0,
		"BUTTON",
		t.Name.c_str(),
		WS_VISIBLE | BS_AUTOCHECKBOX | WS_CHILD,
		10,
		py,
		textSize.cx + 5,
		textSize.cy + 5,
		owner,
		nullptr,
		hInstance, nullptr
	);
}

Setting<bool> SettingsWindow::SettingControl<bool>::GetSetting()
{
	bool value = SendMessageA(_window, BM_GETCHECK, 0, 0) == BST_CHECKED;

	Setting<bool> s = _setting;
	s.Value = value;

	return s;
}

SettingsWindow::SettingControl<float>::SettingControl(Setting<float>& t, HWND owner, HINSTANCE hInstance, int py) :
	SettingControlBase(t)
{
	HDC hdc = GetDC(owner);
	SIZE textSize;
	GetTextExtentPoint32A(hdc, t.Name.c_str(), int(t.Name.length()), &textSize);

	HWND label = CreateWindowExA(
		0,
		"STATIC",
		t.Name.c_str(),
		WS_VISIBLE | WS_CHILD,
		10,
		py,
		textSize.cx + 5,
		textSize.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	std::string v = std::to_string(t.Value);
	textbox = std::make_unique<NumericTextbox>(owner, hInstance, 20 + textSize.cx, 10, 75, textSize.cy + 5, v.c_str());
}

Setting<float> SettingsWindow::SettingControl<float>::GetSetting()
{
	char text[256]{};
	GetWindowTextA(_window, text, 255);

	Setting<float> s = _setting;
	s.Value = std::stof(std::string(text));
	return s;
}

SettingsWindow::SettingControl<std::string>::SettingControl(Setting<std::string>& t, HWND owner, HINSTANCE hInstance, int py) :
	SettingControlBase(t)
{
	HDC hdc = GetDC(owner);
	SIZE size;

	GetTextExtentPointA(hdc, _setting.Name.c_str(), int(_setting.Name.length()), &size);
}

Setting<std::string> SettingsWindow::SettingControl<std::string>::GetSetting()
{
	char text[256]{};
	GetWindowTextA(_window, text, 256);

	Setting<std::string> s = _setting;
	s.Value = std::string(text);
	return s;
}

void SettingsWindow::_createControls()
{
	/*
	_tab = CreateWindowExA(
		0,
		WC_TABCONTROLA,
		"",
		WS_VISIBLE | WS_CHILS | T
		)
	*/
}

SettingsWindow::SettingsWindow(HWND owner, HINSTANCE hInstance) :
	Dialog(owner, hInstance, nullptr, "Settings")
{
}

void SettingsWindow::ShowDialog() const
{

}

SettingsWindow::~SettingsWindow()
{
}