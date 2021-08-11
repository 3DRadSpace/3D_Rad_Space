#pragma once
#include <windows.h>
#include <d3d11.h>
#include "3DRadSpaceDll/Game_DX11.h"
#include "UpdateDownloadManager.h"
#include <cassert>
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

extern HWND MainWindow, RenderWindow;

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR args, int nShowCmd);

LRESULT __stdcall WindowProcessMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WindowProcessEditor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ResizeWindows();
void CheckAndDownloadUpdate();

#define MENU_NEWFILE 300
#define MENU_OPENFILE 301
#define MENU_SAVEFILE 302
#define MENU_SAVEFILEAS 303
#define MENU_PLAYPROJECT 304
#define MENU_COMPILEPROJECT 305
#define MENU_EXIT 306

#define MENU_ADDOBJ 307
#define MENU_ADDPROJECT 308
#define MENU_INSTALLFILES 309
#define MENU_RESETCURSOR 310

#define MENU_UPDATECHECK 311
#define MENU_PREFERENCES 312

#define MENU_ABOUT 313
#define MENU_DOCS 314
#define MENU_HOMEPAGE 315
#define MENU_FORUM 316
#define MENU_GITHUB 317