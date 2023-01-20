#include "EditorWindow.hpp"
#include "resource.h"
#include "Engine3DRadSpace/Error.hpp"
#include <fstream>
#include <CommCtrl.h>
#include "HelperFunctions.hpp"

using namespace Engine3DRadSpace::Logging;

#pragma warning(push)
#pragma warning(disable : 6387) //RaiseFatalErrorIfFalse works just like VERIFY(...) - except errors are reported in a message box.

EditorWindow* gEditorWindow = nullptr;

EditorWindow::EditorWindow(HINSTANCE hInstance, char* cmdArgs) : 
	_hInstance(hInstance),
	mainWindow(nullptr),
	renderWindow(nullptr),
	listBox(nullptr),
	toolbar(nullptr)
{
	gEditorWindow = this;
	//
	//Register the window class
	//
	WNDCLASSA wndclass{};
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = EditorWindow_WndProc;
	wndclass.lpszClassName = EditorWindowClassName;
	wndclass.hIcon = static_cast<HICON>(LoadIconA(hInstance,MAKEINTRESOURCEA(IDI_ICON1)));

	ATOM a = RegisterClassA(&wndclass);
	RaiseFatalErrorIfFalse(a != 0,"Failed to register class!");

	//
	//Create the menu
	//
	HMENU recentProjectsMenu = CreateMenu();
	RaiseFatalErrorIfFalse(recentProjectsMenu != nullptr,"Failed to create File > Recent files menu!");

	std::ifstream recent_projects(RecentProjectFile);
	//Create the file if it doesn't exist or if it is empty
	if (recent_projects.bad() || recent_projects.fail())
	{
		std::ofstream create_recent_projects(RecentProjectFile);
		create_recent_projects.close();

		AppendMenuA(recentProjectsMenu, MF_STRING, 0, "...");
	}
	//Loop each line
	for(int i = 0 ; recent_projects; i++)
	{
		std::string filename;
		std::getline(recent_projects, filename);
		AppendMenuA(recentProjectsMenu, MF_STRING, CMD_OpenRecentFile1 + static_cast<UINT_PTR>(i),filename.c_str());
	}
	recent_projects.close();

	//Create the rest of the menu.
	HMENU fileMenu = CreateMenu();
	RaiseFatalErrorIfFalse(fileMenu != nullptr,"Failed to create the file menu!");

	AppendMenuA(fileMenu, MF_STRING, CMD_NewFile, "New Project (Ctrl+N)");
	AppendMenuA(fileMenu, MF_STRING, CMD_NewFile, "Open Project (Ctrl+O)");
	AppendMenuA(fileMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(recentProjectsMenu), "Recent projects...");
	AppendMenuA(fileMenu, MF_STRING, CMD_SaveProject, "Save Project (Ctrl+S)");
	AppendMenuA(fileMenu, MF_STRING, CMD_SaveProjectAs, "Save Project As (Ctrl+Shift+S)");
	AppendMenuA(fileMenu, MF_STRING, CMD_PlayProject, "Play Project (Ctrl+P)");
	AppendMenuA(fileMenu, MF_STRING, CMD_BuildProject, "Build Project (Ctrl+Shift+B)");
	AppendMenuA(fileMenu, MF_STRING, CMD_Exit, "Exit (Alt+F4)");

	HMENU editMenu = CreateMenu();
	RaiseFatalErrorIfFalse(editMenu != nullptr, "Failed to create the edit menu!");

	AppendMenuA(editMenu, MF_STRING, CMD_AddObject, "Add Object (Ctrl+A)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddAsset, "Add Asset (Ctrl+Shift+N)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddAddon, "Add Addon (Ctrl+Shift+A)");
	AppendMenuA(editMenu, MF_STRING, CMD_ResetCursor, "Reset the 3D cursor");

	HMENU optionsMenu = CreateMenu();
	RaiseFatalErrorIfFalse(optionsMenu != nullptr, "Failed to create the options menu!");

	AppendMenuA(optionsMenu, MF_STRING, CMD_Preferences, "Preferences");
	AppendMenuA(optionsMenu, MF_STRING, CMD_Update, "Search for updates");

	HMENU helpMenu = CreateMenu();
	RaiseFatalErrorIfFalse(helpMenu != nullptr, "Failed to create the help menu!");

	AppendMenuA(helpMenu, MF_STRING,CMD_About, "About");
	AppendMenuA(helpMenu, MF_STRING, CMD_Documentation, "Documentation");
	AppendMenuA(helpMenu, MF_STRING, CMD_Homepage, "Homepage");
	AppendMenuA(helpMenu, MF_STRING, CMD_Github, "Github");

	HMENU mainMenu = CreateMenu();
	RaiseFatalErrorIfFalse(mainMenu != nullptr, "Failed to create the main menu!");

	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(fileMenu), "File");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(editMenu), "Edit");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(optionsMenu), "Options");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(helpMenu), "Help");

	//Create window
	mainWindow = CreateWindowExA(
		WS_EX_ACCEPTFILES,
		EditorWindowClassName,
		"3DRadSpace v0.1.0a",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		nullptr,
		mainMenu,
		hInstance,
		nullptr);

	RaiseFatalErrorIfFalse(mainWindow != nullptr, "Failed to create the main window!");

	//Create controls
	toolbar = CreateWindowExA(
		0,
		TOOLBARCLASSNAMEA,
		"",
		TBSTYLE_FLAT | WS_CHILD | WS_VISIBLE,
		0,
		0,
		800,
		25,
		mainWindow,
		nullptr,
		hInstance,
		nullptr
	);
	RaiseFatalErrorIfFalse(toolbar != nullptr, "Failed to create the toolbar!");

	listBox = CreateWindowExA(
		0,
		WC_TREEVIEWA,
		"",
		TVS_CHECKBOXES | WS_CHILD | WS_VISIBLE,
		0,
		0,
		150,
		600,
		mainWindow,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindow(mainWindow, SW_MAXIMIZE);
}

LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps{};
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_3DSHADOW + 1));
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CLOSE:
			exit(0);
			break;
		case WM_COMMAND:
		{
			switch (wParam)
			{
				case CMD_NewFile:
					break;
				case CMD_OpenFile:
					break;
				case CMD_OpenRecentFile1:
					break;
				case CMD_SaveProject:
					break;
				case CMD_SaveProjectAs:
					break;
				case CMD_PlayProject:
					break;
				case CMD_BuildProject:
					break;
				case CMD_Exit:
					exit(0);
					break;
				case CMD_AddObject:
					break;
				case CMD_AddAsset:
					break;
				case CMD_AddAddon:
					break;
				case CMD_ResetCursor:
					break;
				case CMD_Preferences:
					break;
				case CMD_Update:
					break;
				case CMD_About:
					break;
				case CMD_Documentation:
					break;
				case CMD_Homepage:
					break;
				case CMD_Github:
					break;
				default: break;
			}
			break;
		}
		case WM_SIZE:
		{
			RECT rcWnd{};
			GetClientRect(hwnd, &rcWnd);
			int wndWidth = rcWnd.right - rcWnd.left;
			int wndHeight = rcWnd.bottom - rcWnd.top;

			RECT rcToolbar{};
			GetWindowRect(gEditorWindow->toolbar, &rcToolbar);
			int toolbarHeight = rcToolbar.bottom - rcToolbar.top;

			SetWindowPos(gEditorWindow->listBox, nullptr, 0, toolbarHeight + 1, 150, wndHeight - toolbarHeight, 0);
			SetWindowPos(gEditorWindow->toolbar, nullptr, 0, 0, wndWidth, 25, 0);
			break;
		}
		default: break;
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

#pragma warning(pop)