#include "UpdateProgressWindow.hpp"
#include "Engine3DRadSpace/Logging/Exception.hpp"
#include <CommCtrl.h>
using namespace Engine3DRadSpace::Logging;

UpdateProgressWindow* UpdateProgressWindow::gInstance = nullptr;

LRESULT UpdateProgressWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        FillRect(ps.hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW));
        EndPaint(hwnd, &ps);
		break;
    }
    case WM_COMMAND:
    	{
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				if(reinterpret_cast<HWND>(lParam) == UpdateProgressWindow::gInstance->_cancelButton)
					UpdateProgressWindow::gInstance->_state->Abort();
				break;
			default:
				break;
			}
			break;
	    }
    default:
		break;
    }
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

UpdateProgressWindow::UpdateProgressWindow(HINSTANCE hInstance, AutoupdaterState* state):
	_state(state),
	shownProgress(0),
	_hInstance(hInstance)
{
    constexpr auto UpdateProgressWindowClassName = "3DRSP_UpdateProgress";

    WNDCLASSA wndClass{};
    wndClass.lpszClassName = UpdateProgressWindowClassName;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(nullptr, IDI_INFORMATION);
    wndClass.lpfnWndProc = UpdateProgressWindowProc;

    RegisterClassA(&wndClass);

    _window = CreateWindowExA(
        0,
        UpdateProgressWindowClassName,
        "Downloading update...",
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        350,
        150,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

	HWND label1 = CreateWindowExW(
		0,
		L"Static",
		L"Downloading update...",
		WS_VISIBLE | WS_CHILD,
		120,
		10,
		300,
		20,
		_window,
		nullptr,
		hInstance,
		nullptr
	);

	HWND label2 = CreateWindowExW(
		0,
		L"STATIC",
		L"Progress:",
		WS_VISIBLE | WS_CHILD,
		10,
		30,
		100,
		20,
		_window,
		nullptr,
		hInstance,
		nullptr
	);

	_progressBar = CreateWindowExW(
		0,
		PROGRESS_CLASS,
		nullptr,
		WS_VISIBLE | WS_CHILD | PBS_SMOOTH,
		80,
		30,
		200,
		20,
		_window,
		nullptr,
		hInstance,
		nullptr
	);

	_cancelButton = CreateWindowExW(
		0,
		L"Button",
		L"Cancel",
		WS_VISIBLE | WS_CHILD,
		140,
		60,
		70,
		25,
		_window,
		nullptr,
		hInstance,
		nullptr
	);

	SendMessageW(_progressBar, PBM_SETSTEP, 1, 0);
	SendMessageW(_progressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));

    ShowWindow(_window, SW_NORMAL);
    ShowWindow(label1, SW_NORMAL);
    ShowWindow(label2, SW_NORMAL);
    ShowWindow(_progressBar, SW_NORMAL);
	ShowWindow(_cancelButton, SW_NORMAL);

	gInstance = this;
}

HWND UpdateProgressWindow::GetWindow() const
{
	return _window;
}

bool UpdateProgressWindow::Sync()
{
	if (!_state->Initialized()) return false;
	if (_state->Finished())
	{
		shownProgress = 100;
		return true;
	}

	const int currentProgress = static_cast<int>(_state->GetCurrentProgress() * 100.f);
	while (shownProgress < currentProgress)
	{
		SendMessageA(_progressBar, PBM_STEPIT, 0, 0);
		++shownProgress;
	}
	return false;
}

UpdateProgressWindow::~UpdateProgressWindow()
{
	DestroyWindow(_window);
	_window = nullptr;
	UnregisterClassA("3DRSP_UpdateProgress", _hInstance);
}
