#include "CrashWindow.hpp"
#include <format>

INT_PTR WINAPI CrashWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CrashWindow* wndCrash = nullptr;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		wndCrash = reinterpret_cast<CrashWindow*>(lParam);
		wndCrash->window = hwnd;
		wndCrash->_createControls();
		return 1;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			DestroyWindow(hwnd);
			return TRUE;
		}
		if (HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == wndCrash->_okButton)
		{
			DestroyWindow(hwnd);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return TRUE;
	case WM_DESTROY:
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

CrashWindow::CrashWindow(HWND owner, HINSTANCE hInstance, const std::exception& e, const std::stacktrace& stacktrace) :
	Dialog(owner, hInstance, CrashWindow_DlgProc, "3DRadSpace - Crash Report", 210, 100),
	_exceptionMessage(std::format("An exception of type {} was thrown\r\nException message:{}\r\nStacktrace:\r\n\r\n",
		typeid(e).name(), e.what()))
{
	for (auto& line : stacktrace)
	{
		_exceptionMessage += std::to_string(line);
		_exceptionMessage += "\r\n";
	}
}

void CrashWindow::_createControls()
{
	_titleLabel = CreateWindowExA(
		0,
		"Static",
		"An unrecoverable error occurred.",
		WS_VISIBLE | WS_CHILD,
		10, 10, 390, 20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	_exceptionTextbox = CreateWindowExA(
		WS_EX_CLIENTEDGE,
		"Edit",
		_exceptionMessage.c_str(),
		WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_HSCROLL,
		10, 35, 390, 110,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	_okButton = CreateWindowExA(
		0,
		"Button",
		"OK",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		300, 155, 100, 30,
		window,
		reinterpret_cast<HMENU>(IDOK),
		hInstance,
		nullptr
	);
}

void CrashWindow::ShowDialog()
{
	HWND hwnd = CreateDialogIndirectParamW(
		hInstance,
		this->dialogTemplate,
		owner,
		CrashWindow_DlgProc,
		reinterpret_cast<LPARAM>(this)
	);
	if (hwnd == nullptr) return;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	bool hadQuitMessage = false;
	int quitCode = 0;

	MSG msg;
	while (IsWindow(hwnd))
	{
		const BOOL gm = GetMessageA(&msg, nullptr, 0, 0);
		if (gm == -1) break;
		if (gm == 0)
		{
			hadQuitMessage = true;
			quitCode = static_cast<int>(msg.wParam);
			continue;
		}

		if (!IsDialogMessage(hwnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	if (hadQuitMessage) PostQuitMessage(quitCode);
}
