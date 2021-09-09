#pragma once
#include "Libs.h"
#include "resource.h"
#include <Mouse.h>
#include "DownloadStatusWindow.h"
#include <dxgidebug.h>
#include <discord_rpc.h>

extern HWND MainWindow, RenderWindow, ToolBarWindow;

extern std::wstring CurrentFile;

extern HINSTANCE hGlobCurrentInst;

extern bool IsSaved, _3DMode;

int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_  PWSTR args, _In_  int nShowCmd);

LRESULT __stdcall WindowProcessMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WindowProcessEditor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ResizeWindows();
void CheckUpdate();
void DownloadUpdate(char* link,char* version);

void StartDiscordPresence();

void ResetLoadedProject();
bool ShowProjectNotSavedWarning();
void SaveProject();
void SaveProjectAs();

void UpdateDiscordRichPresence();
void StopDiscordRichPresence();

void ExitEditor();

Point GetRenderWindowResolution();

constexpr int MENU_NEWFILE = 300;
constexpr int MENU_OPENFILE = 301;
constexpr int MENU_SAVEFILE = 302;
constexpr int MENU_SAVEFILEAS = 303;
constexpr int MENU_PLAYPROJECT = 304;
constexpr int MENU_COMPILEPROJECT = 305;
constexpr int MENU_EXIT = 306;

constexpr int MENU_ADDOBJ = 307;
constexpr int MENU_ADDPROJECT = 308;
constexpr int MENU_RESETCURSOR = 309;
constexpr int MENU_IMPORTRESOURCES = 310;

constexpr int MENU_UPDATECHECK = 311;
constexpr int MENU_PREFERENCES = 312;

constexpr int MENU_ABOUT = 313;
constexpr int MENU_DOCS = 314;
constexpr int MENU_HOMEPAGE = 315;
constexpr int MENU_FORUM = 316;
constexpr int MENU_GITHUB = 317;

constexpr int MENU_SWITCH3D2D = 318;

constexpr const char* __3DRADSPACE_VERSION = "0.1.0";
constexpr const wchar_t* __3DRADSPACE_FD_FILTER = L"3DRadSpace Project (*.3drsp)\0*.3drsp";