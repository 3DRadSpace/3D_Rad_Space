#pragma once
#include <Windows.h>
#include <CommCtrl.h>
#include "UpdateDownloadManager.h"

class DownloadStatusWindow
{
	static HINSTANCE hInstance;
	static HWND window, label1, label2, progressbar, cancelbutton;
	static int _shownprogress;
	static int _currentprogress;
public: 
	static UpdateDownloadManager* downloadmanager;

	static void Register(HINSTANCE hInstance);
	static bool Registered;

	static void Create(HWND parent);
	static void SetManager(UpdateDownloadManager* manager);
	static void SyncProgress();
	static UpdateDownloadManagerDestructorNotifier f;
	static HWND GetWindow();
	static HWND GetCancelButton();

	static void Reset();

	static bool Finished;
	static bool Cancelled;

};
LRESULT __stdcall DownloadWindowEventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void UpdateDownloadManagerDestructorNotificationFunction(unsigned long& p, unsigned long& s);


