#pragma once
#include "../AutoupdaterState.hpp"

class UpdateProgressWindow
{
	AutoupdaterState* _state;
	HINSTANCE _hInstance;
	HWND _window;

	HWND _cancelButton;

	HWND _progressBar;
	int shownProgress;

	static UpdateProgressWindow* gInstance;
public:
	UpdateProgressWindow(HINSTANCE hInstance, AutoupdaterState* state);

	HWND GetWindow() const;

	friend LRESULT UpdateProgressWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Sync();

	~UpdateProgressWindow();
};

LRESULT UpdateProgressWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);