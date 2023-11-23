#include "SettingsWindow.hpp"
#include "../Controls/NumericTextbox.hpp"

SettingsWindow::SettingControl<bool>::SettingControl(Setting<bool>& t, HWND owner, HINSTANCE hInstance, int py) :
	SettingControlBase(t)
{
	HDC hdc = GetDC(owner);
	SIZE textSize;
	GetTextExtentPoint32A(hdc, t.Name.c_str(), t.Name.length(), &textSize);

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
	return Setting<bool>
	{
		.Category = _setting.Category,
		.Name = _setting.Name,
		.Value = value
	};
}

SettingsWindow::SettingControl<float>::SettingControl(Setting<float>& t, HWND owner, HINSTANCE hInstance, int py) :
	SettingControlBase(t)
{
	HDC hdc = GetDC(owner);
	SIZE textSize;
	GetTextExtentPoint32A(hdc, t.Name.c_str(), t.Name.length(), &textSize);

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
}

SettingsWindow::SettingsWindow(HWND owner, HINSTANCE hInstance) :
	Dialog(owner, hInstance, nullptr, "Settings")
{
}

SettingsWindow::~SettingsWindow()
{
}
