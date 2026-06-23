#include "AboutWindow.hpp"
#include "../../resource.h"

INT_PTR WINAPI AboutWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static AboutWindow* wndAbout = nullptr;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		wndAbout = reinterpret_cast<AboutWindow*>(lParam);
		wndAbout->window = hwnd;
		wndAbout->_createControls();
		return 1;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			return TRUE;
		default:
			break;
		}
		if (HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == wndAbout->_okButton)
		{
			EndDialog(hwnd, IDOK);
			return TRUE;
		}
		break;
	default:
		break;
	}
	return FALSE;
}

AboutWindow::AboutWindow(HWND owner, HINSTANCE hInstance) : Dialog(owner, hInstance, AboutWindow_DlgProc, "About 3DRadSpace", 260, 130)
{
}

void AboutWindow::_createControls()
{
	_iconPictureBox = CreateWindowExA(
		0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD | SS_ICON,
		10, 10, 200, 200,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	HICON hIcon = (HICON)LoadImageA(
		hInstance,
		MAKEINTRESOURCEA(IDI_ICON1),
		IMAGE_ICON,
		200, 200,
		LR_DEFAULTCOLOR
	);
	if (hIcon == nullptr)
	{
		MessageBoxA(window, "Failed to load the icon for the about window!", "Error", MB_ICONERROR);
	}
	else
	{
		SendMessageA(_iconPictureBox, STM_SETICON, reinterpret_cast<WPARAM>(hIcon), 0);
	}

	_label = CreateWindowExA(
		0,
		"Static",
		"3DRadSpace Editor\nVersion 0.1.0Alpha\n\nhttps://3dradspace.github.io\n\n\n\nThis software is licensed under MIT.",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		220, 10, 200, 200,
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
		390, 220, 100, 30,
		window,
		reinterpret_cast<HMENU>(IDOK),
		hInstance,
		nullptr
	);
}

void AboutWindow::ShowDialog()
{
	Dialog::ShowDialog(static_cast<void*>(this));
}