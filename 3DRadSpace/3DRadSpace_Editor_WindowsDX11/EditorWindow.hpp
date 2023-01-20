#pragma once
#include <Windows.h>

constexpr const char* EditorWindowClassName = "CLASS_3DRADSPACE_MAINWINDOW";
constexpr const char* RecentProjectFile = "Data\\RecentProjects.txt";

constexpr int CMD_NewFile = 500;
constexpr int CMD_OpenFile = 501;

constexpr int CMD_OpenRecentFile1 = 502;
//constexpr int CMD_OpenRecentFile10 = 511; 

constexpr int CMD_SaveProject = 512;
constexpr int CMD_SaveProjectAs = 513;
constexpr int CMD_PlayProject = 514;
constexpr int CMD_BuildProject = 515;
constexpr int CMD_Exit = 516;

constexpr int CMD_AddObject = 517;
constexpr int CMD_AddAsset = 518;
constexpr int CMD_AddAddon = 519;
constexpr int CMD_ResetCursor = 520;

constexpr int CMD_Preferences = 521;
constexpr int CMD_Update = 522;

constexpr int CMD_About = 523;
constexpr int CMD_Documentation = 524;
constexpr int CMD_Homepage = 525;
constexpr int CMD_Github = 526;

class EditorWindow
{
	HINSTANCE _hInstance;
	HWND mainWindow;
	HWND renderWindow;
	HWND listBox;
	HWND toolbar;
public:
	EditorWindow(HINSTANCE hInstance, char* cmdArgs);;

	friend LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);