#pragma once
#include "../Settings.hpp"
#include "../Controls/Dialog.hpp"

class SettingsWindow : public Dialog
{
	template<typename T>
	class SettingControl{ };

	template<typename T>
	class SettingControlBase
	{
	protected:
		SettingControlBase(Setting<T>& s) : _setting(s) {}
		Setting<T>& _setting;
	};

	template<>
	class SettingControl<void>
	{
	protected:
		HWND _window = nullptr;
	public:
		virtual ~SettingControl<void>() = default;
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

	HWND _okButton;
	HWND _cancelButton;
public:
	SettingsWindow(HWND owner, HINSTANCE hInstance);

	SettingsWindow(SettingsWindow&) = delete;
	SettingsWindow(SettingsWindow&&) = delete;

	SettingsWindow& operator=(SettingsWindow&) = delete;
	SettingsWindow& operator=(SettingsWindow&&) = delete;

	~SettingsWindow();
};