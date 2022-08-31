#include "DownloadStatusWindow.hpp"

HWND DownloadStatusWindow::window = nullptr;
HWND DownloadStatusWindow::label1 = nullptr;
HWND DownloadStatusWindow::label2 = nullptr;
HWND DownloadStatusWindow::progressbar = nullptr;
HWND DownloadStatusWindow::cancelbutton = nullptr;
HINSTANCE DownloadStatusWindow::hInstance = nullptr;
int DownloadStatusWindow::_shownprogress = 0;
int DownloadStatusWindow::_currentprogress = 0;
UpdateDownloadManager* DownloadStatusWindow::downloadmanager = nullptr;
bool DownloadStatusWindow::Finished = false;
bool DownloadStatusWindow::Cancelled = false;
bool DownloadStatusWindow::Registered = false;

void DownloadStatusWindow::Register(HINSTANCE hInstance)
{
	if (Registered) return;
	else Registered = true;

	cancelbutton = nullptr;
	DownloadStatusWindow::hInstance = hInstance;
	label1 = nullptr;
	label2 = nullptr;
	progressbar = nullptr;
	window = nullptr;

	WNDCLASS wndclass;
	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.lpfnWndProc = DownloadWindowEventHandler;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = TEXT("3DRADSPACE_UPDATE_DOWNLOAD_PROGRESS");
	wndclass.hIcon = LoadIcon(nullptr, IDI_INFORMATION);
	
	RegisterClass(&wndclass);

	_shownprogress = 0;

}

void DownloadStatusWindow::Create(HWND parent)
{
	window = CreateWindowExW(
		0,
		L"3DRADSPACE_UPDATE_DOWNLOAD_PROGRESS",
		L"Downloading Update...",
		 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		400,
		400,
		350,
		150,
		nullptr,
		nullptr,
		DownloadStatusWindow::hInstance,
		nullptr
	);

	label1 = CreateWindowExW(
		0,
		L"Static",
		L"Downloading update...",
		WS_VISIBLE | WS_CHILD,
		120,
		10,
		300,
		20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	label2 = CreateWindowExW(
		0,
		L"STATIC",
		L"Progress:",
		WS_VISIBLE | WS_CHILD,
		10,
		30,
		100,
		20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	progressbar = CreateWindowExW(
		0,
		PROGRESS_CLASS,
		nullptr,
		WS_VISIBLE | WS_CHILD,
		80,
		30,
		200,
		20,
		window,
		nullptr,
		hInstance,
		nullptr
	);
	
	SendMessageW(progressbar, PBM_SETSTEP, 1, 0);
	SendMessageW(progressbar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));

	cancelbutton = CreateWindowExW(
		0,
		L"Button", 
		L"Cancel",
		WS_VISIBLE | WS_CHILD,
		140,
		60,
		70,
		25,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindow(window, SW_NORMAL);
	ShowWindow(label1, SW_NORMAL);
	ShowWindow(label2, SW_NORMAL);
	ShowWindow(progressbar, SW_NORMAL);
	ShowWindow(cancelbutton, SW_NORMAL);

	MSG msg;
	memset(&msg, 0, sizeof(MSG));
	while (GetMessageW(&msg, window, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
		if(!Finished) DownloadStatusWindow::SyncProgress();
		if (Finished) break;
	}
}

void DownloadStatusWindow::SetManager(UpdateDownloadManager* manager)
{
	DownloadStatusWindow::downloadmanager = manager;
	manager->DestructorNotFunc = UpdateDownloadManagerDestructorNotificationFunction;
}

void DownloadStatusWindow::SyncProgress()
{
	if (Finished) return;
	if (downloadmanager->GetFinishedState())
	{
		_shownprogress = 100;
		return;
	}
	ULONG pC = downloadmanager->GetProgress();
	ULONG pM = downloadmanager->GetProgressMax();

	float pR = (float)pC / (float)pM; // progress ratio

	if (pC == pM && pM == 0)
	{
		_shownprogress = 0;
		_currentprogress = 0;
		return;
	}

	_currentprogress = (int)(pR * 100);
	while (_shownprogress < _currentprogress)
	{
		SendMessageW(progressbar, PBM_STEPIT, 0, 0);
		_shownprogress++;
	}
}

HWND DownloadStatusWindow::GetWindow()
{
	return window;
}

HWND DownloadStatusWindow::GetCancelButton()
{
	return cancelbutton;
}
void DownloadStatusWindow::Reset()
{
	Finished = false;
	Cancelled = false;
	_currentprogress = 0;
	_shownprogress = 0;
}

LRESULT __stdcall DownloadWindowEventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT pstr;
			HDC hdc = BeginPaint(hwnd, &pstr);
			FillRect(hdc, &pstr.rcPaint,CreateSolidBrush(RGB(240,240,240)));
			EndPaint(hwnd, &pstr);
			break;
		}
		case WM_COMMAND:
		{
			switch (HIWORD(wParam))
			{
				case BN_CLICKED:
				{
					if ((HWND)lParam == DownloadStatusWindow::GetCancelButton()) // >.<
					{
						DownloadStatusWindow::Finished = false;
						DownloadStatusWindow::Cancelled = true;
						DownloadStatusWindow::downloadmanager->Abort();
						PostMessage(hwnd, WM_CLOSE, 0, 0);
						break;
					}
					break;
				}
				default: break;
			}
		}
		case WM_CLOSE:
		{
			DownloadStatusWindow::Finished = false;
			DownloadStatusWindow::Cancelled = true;
			DownloadStatusWindow::downloadmanager->Abort();
			break;
		}
		default:break;
	}
	
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void UpdateDownloadManagerDestructorNotificationFunction(unsigned long& p, unsigned long& s)
{
	PostMessageW(DownloadStatusWindow::GetWindow(), WM_CLOSE, 0, 0);
	DownloadStatusWindow::Finished = true;
}
