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
		int _cy = 0;
	public:
		HWND GetHandle();
		int AccY();

		virtual void GetSetting() = 0;

		virtual ~SettingControl<void>() = default;
	};

	template<>
	class SettingControl<bool> final : public SettingControl<void>, public SettingControlBase<bool>
	{
	public:
		SettingControl(Setting<bool>& t, HWND owner, HINSTANCE hInstance, int py);
		void GetSetting() override;
	};

	template<>
	class SettingControl<float> final : public SettingControl<void>, public SettingControlBase<float>
	{
		std::unique_ptr<NumericTextbox> textbox;
	public:
		SettingControl(Setting<float>& t, HWND owner, HINSTANCE hInstance, int py);
		void GetSetting() override;
	};

	template<>
	class SettingControl<std::string> final : public SettingControl<void>, public SettingControlBase<std::string>
	{
	public:
		SettingControl(Setting<std::string>& t, HWND owner, HINSTANCE hInstance, int py);
		void GetSetting() override;
	};

	HWND _tab = nullptr;
	HWND _okButton = nullptr;
	HWND _cancelButton = nullptr;

	std::vector<std::unique_ptr<SettingControl<void>>> _controls;

	template<typename T>
	void _addSetting(Setting<T>& setting)
	{
		std::unique_ptr<SettingControl<void>> ctrl;
		ctrl.reset(new SettingControl<T>(setting, window, hInstance, _cy));
		_cy += ctrl->AccY() + 5;

		_controls.push_back(std::move(ctrl));
	}

	int _cy = 10;

	void _createControls();
public:
	SettingsWindow(HWND owner, HINSTANCE hInstance);

	SettingsWindow(SettingsWindow&) = delete;
	SettingsWindow(SettingsWindow&&) = delete;

	SettingsWindow& operator=(SettingsWindow&) = delete;
	SettingsWindow& operator=(SettingsWindow&&) = delete;

	bool ShowDialog();

	~SettingsWindow();

	friend INT_PTR SettingsWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};