#pragma once
#include "../Settings.hpp"
#include "../Controls/Dialog.hpp"
#include "../Controls/NumericTextbox.hpp"
#include "../../Includes.hpp"

INT_PTR SettingsWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class SettingsWindow final : public Dialog
{
private:
	template<typename T>
	class SettingControl{ };

	template<typename T>
	class SettingControlBase
	{
	protected:
		SettingControlBase(Setting<T>& s) : _setting(s) {}
		Setting<T>& _setting;
	public:
		virtual ~SettingControlBase() = default;
	};

	template<>
	class SettingControl<void>
	{
	protected:
		HWND _window = nullptr;
	public:
		virtual ~SettingControl<void>() = default;

		HWND GetHandle();
	};

	template<>
	class SettingControl<bool> final : public SettingControl<void>, public SettingControlBase<bool>
	{
	public:
		SettingControl(Setting<bool>& t, HWND owner, HINSTANCE hInstance, int py);
		Setting<bool> GetSetting();
	};

	template<>
	class SettingControl<float> final : public SettingControl<void>, public SettingControlBase<float>
	{
		std::unique_ptr<NumericTextbox> textbox;
	public:
		SettingControl(Setting<float>& t, HWND owner, HINSTANCE hInstance, int py);
		Setting<float> GetSetting();
	};

	template<>
	class SettingControl<std::string> final : public SettingControl<void>, public SettingControlBase<std::string>
	{
	public:
		SettingControl(Setting<std::string>& t, HWND owner, HINSTANCE hInstance, int py);
		Setting<std::string> GetSetting();
	};

	HWND _tab;
	HWND _okButton;
	HWND _cancelButton;

	std::vector<SettingControl<void>> _controls;

	void _createControls();
public:
	SettingsWindow(HWND owner, HINSTANCE hInstance);

	SettingsWindow(SettingsWindow&) = delete;
	SettingsWindow(SettingsWindow&&) = delete;

	SettingsWindow& operator=(SettingsWindow&) = delete;
	SettingsWindow& operator=(SettingsWindow&&) = delete;

	void ShowDialog() const;

	~SettingsWindow();

	friend INT_PTR SettingsWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};