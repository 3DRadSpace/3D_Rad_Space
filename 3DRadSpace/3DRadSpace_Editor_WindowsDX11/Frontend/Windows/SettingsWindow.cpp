#include "SettingsWindow.hpp"
#include <algorithm>
#include "../HelperFunctions.hpp"

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
			return 1;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
			EndPaint(hwnd, &ps);
			return 1;
		}
		case WM_COMMAND:
		{
			switch (HIWORD(wParam))
			{
				case BN_CLICKED:
				{
					if (lParam == reinterpret_cast<LPARAM>(settingsWindow->_okButton))
					{
						for (auto& setting : settingsWindow->_controls)
						{
							setting->GetSetting();
						}
						Settings::Save();
						EndDialog(hwnd, IDOK);
					}
					if (lParam == reinterpret_cast<LPARAM>(settingsWindow->_cancelButton))
					{
						EndDialog(hwnd, IDCANCEL);
					}
					break;
				}
				default:
					break;
			}
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

int SettingsWindow::SettingControl<void>::AccY()
{
	return _cy;
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
		textSize.cx + 25,
		textSize.cy + 5,
		owner,
		nullptr,
		hInstance, nullptr
	);

	SendMessageA(_window, BM_SETCHECK, t.Value ? BST_CHECKED : BST_UNCHECKED, 0);
	_cy = textSize.cy + 5;
}

void SettingsWindow::SettingControl<bool>::GetSetting()
{
	_setting.Value = SendMessageA(_window, BM_GETCHECK, 0, 0) == BST_CHECKED;;
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
	_window = static_cast<HWND>(*textbox);
	_cy = textSize.cy + 5;
}

void SettingsWindow::SettingControl<float>::GetSetting()
{
	char text[256]{};
	GetWindowTextA(_window, text, 255);

	_setting.Value = std::clamp(std::stof(std::string(text)), _setting.Min, _setting.Max);
}

SettingsWindow::SettingControl<std::string>::SettingControl(Setting<std::string>& t, HWND owner, HINSTANCE hInstance, int py) :
	SettingControlBase(t)
{
	HDC hdc = GetDC(owner);
	SIZE size;

	GetTextExtentPointA(hdc, _setting.Name.c_str(), int(_setting.Name.length()), &size);

	HWND label = CreateWindowExA(
		0,
		"STATIC",
		t.Name.c_str(),
		WS_VISIBLE | WS_CHILD,
		10,
		py,
		size.cx + 5,
		size.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_window = CreateWindowExA(
		0,
		"EDIT",
		t.Value.c_str(),
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		10,
		py,
		75,
		size.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);
	
	_cy = size.cy + 5;
}

void SettingsWindow::SettingControl<std::string>::GetSetting()
{
	char text[256]{};
	GetWindowTextA(_window, text, 256);

	_setting.Value = std::string(text);
}

void SettingsWindow::_createControls()
{
	_addSetting(Settings::CameraSensitivity);
	_addSetting(Settings::StartupUpdate);
	_addSetting(Settings::ShowGrid);

	HDC hdc = GetDC(window);

	SIZE textSize;
	GetTextExtentPointA(hdc, "Cancel", 7, &textSize);

	_cancelButton = CreateWindowExA(
		0,
		"Button",
		"Cancel",
		WS_VISIBLE | WS_CHILD,
		10,
		_cy,
		textSize.cx + 5,
		textSize.cy + 5,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	int accX = textSize.cx + 20;
	GetTextExtentPointA(hdc, "OK", 2, &textSize);

	_okButton = CreateWindowExA(
		0,
		"Button",
		"OK",
		WS_VISIBLE | WS_CHILD,
		accX,
		_cy,
		textSize.cx + 5,
		textSize.cy + 5,
		window,
		nullptr,
		hInstance,
		nullptr
	);
	_cy += textSize.cy + 5;

	SetWindowPos(window, nullptr, 0, 0, 250, _cy + GetTitleBarHeight() + 20, SWP_NOMOVE);
}

SettingsWindow::SettingsWindow(HWND owner, HINSTANCE hInstance) :
	Dialog(owner, hInstance, SettingsWindow_DlgProc, "Settings")
{
}

bool SettingsWindow::ShowDialog()
{
	return Dialog::ShowDialog(static_cast<void*>(this)) == IDOK;
}

SettingsWindow::~SettingsWindow()
{
}