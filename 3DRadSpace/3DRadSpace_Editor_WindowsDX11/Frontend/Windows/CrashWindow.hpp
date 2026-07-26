#pragma once
#include "../Controls/Dialog.hpp"
#include <exception>
#include <string>
#include <stacktrace>

class CrashWindow : public Dialog
{
	HWND _titleLabel = nullptr;
	HWND _exceptionTextbox = nullptr;
	HWND _okButton = nullptr;
	std::string _exceptionMessage;

	void _createControls();
public:
	CrashWindow(HWND owner, HINSTANCE hInstance, const std::exception& e, const std::stacktrace& stacktrace);

	void ShowDialog();

	friend INT_PTR WINAPI CrashWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
