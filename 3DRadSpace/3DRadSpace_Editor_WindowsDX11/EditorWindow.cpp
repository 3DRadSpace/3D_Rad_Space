#include "EditorWindow.hpp"
#include "resource.h"
#include "Engine3DRadSpace/Error.hpp"
#include <fstream>
#include <CommCtrl.h>
#include "HelperFunctions.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;

EditorWindow* gEditorWindow = nullptr;

EditorWindow::EditorWindow(HINSTANCE hInstance, char* cmdArgs) : 
	_hInstance(hInstance),
	_mainWindow(nullptr),
	_listBox(nullptr),
	_toolbar(nullptr),
	_running(true)
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
	RaiseFatalErrorIfNull(recentProjectsMenu,"Failed to create File > Recent files menu!");

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
	RaiseFatalErrorIfNull(fileMenu,"Failed to create the file menu!");

	AppendMenuA(fileMenu, MF_STRING, CMD_NewFile, "New Project (Ctrl+N)");
	AppendMenuA(fileMenu, MF_STRING, CMD_OpenFile, "Open Project (Ctrl+O)");
	AppendMenuA(fileMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(recentProjectsMenu), "Recent projects...");
	AppendMenuA(fileMenu, MF_STRING, CMD_SaveProject, "Save Project (Ctrl+S)");
	AppendMenuA(fileMenu, MF_STRING, CMD_SaveProjectAs, "Save Project As (Ctrl+Shift+S)");
	AppendMenuA(fileMenu, MF_STRING, CMD_PlayProject, "Play Project (Ctrl+P)");
	AppendMenuA(fileMenu, MF_STRING, CMD_BuildProject, "Build Project (Ctrl+Shift+B)");
	AppendMenuA(fileMenu, MF_STRING, CMD_Exit, "Exit (Alt+F4)");

	HMENU editMenu = CreateMenu();
	RaiseFatalErrorIfNull(editMenu, "Failed to create the edit menu!");

	AppendMenuA(editMenu, MF_STRING, CMD_AddObject, "Add Object (Ctrl+A)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddAsset, "Add Asset (Ctrl+Shift+N)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddAddon, "Add Addon (Ctrl+Shift+A)");
	AppendMenuA(editMenu, MF_STRING, CMD_ResetCursor, "Reset the 3D cursor");

	HMENU optionsMenu = CreateMenu();
	RaiseFatalErrorIfNull(optionsMenu, "Failed to create the options menu!");

	AppendMenuA(optionsMenu, MF_STRING, CMD_Preferences, "Preferences");
	AppendMenuA(optionsMenu, MF_STRING, CMD_Update, "Search for updates");

	HMENU helpMenu = CreateMenu();
	RaiseFatalErrorIfNull(helpMenu, "Failed to create the help menu!");

	AppendMenuA(helpMenu, MF_STRING,CMD_About, "About");
	AppendMenuA(helpMenu, MF_STRING, CMD_Documentation, "Documentation");
	AppendMenuA(helpMenu, MF_STRING, CMD_Homepage, "Homepage");
	AppendMenuA(helpMenu, MF_STRING, CMD_Github, "Github");

	HMENU mainMenu = CreateMenu();
	RaiseFatalErrorIfNull(mainMenu, "Failed to create the main menu!");

	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(fileMenu), "File");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(editMenu), "Edit");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(optionsMenu), "Options");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(helpMenu), "Help");

	//Create window
	_mainWindow = CreateWindowExA(
		WS_EX_ACCEPTFILES,
		EditorWindowClassName,
		"3DRadSpace v0.1.0a - Editor",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		nullptr,
		mainMenu,
		hInstance,
		nullptr);

	RaiseFatalErrorIfNull(_mainWindow, "Failed to create the main window!");

	//Create controls
	_toolbar = CreateWindowExA(
		0,
		TOOLBARCLASSNAMEA,
		"",
		TBSTYLE_LIST | WS_CHILD,
		0,
		0,
		800,
		25,
		_mainWindow,
		nullptr,
		hInstance,
		nullptr
	);
	RaiseFatalErrorIfNull(_toolbar, "Failed to create the toolbar!");

	HIMAGELIST toolbarImageList = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 8, 1);
	RaiseFatalErrorIfNull(toolbarImageList, "Failed to create the toolbar image list!");

	
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON2)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON3)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON4)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON5)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON6)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON7)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON8)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON9)));
	
	SendMessageA(_toolbar, TB_SETIMAGELIST, 0, reinterpret_cast<LPARAM>(toolbarImageList));
	SendMessageA(_toolbar, TB_LOADIMAGES, 0, (LPARAM)hInstance);
	
	TBBUTTON tbButtons[8] =
	{
		{ 0, CMD_NewFile,  TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"New" },
		{ 1, CMD_OpenFile, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Open"},
		{ 2, CMD_SaveProject, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Save"},
		{ 3, CMD_SaveProjectAs, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Save As"},
		{ 4, CMD_OpenIDE, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Open IDE"},
		{ 5, CMD_BuildProject, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Build"},
		{ 6, CMD_PlayProject, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Play"},
		{ 7, CMD_Switch2D3D, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Switch to 2D"},
	};
	
	SendMessageA(_toolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessageA(_toolbar, TB_ADDBUTTONS, 8, (LPARAM)&tbButtons);
	
	SendMessageA(_toolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(_toolbar, SW_NORMAL);

	_listBox = CreateWindowExA(
		0,
		WC_TREEVIEWA,
		"",
		TVS_CHECKBOXES | WS_CHILD | WS_VISIBLE,
		0,
		0,
		150,
		600,
		_mainWindow,
		nullptr,
		hInstance,
		nullptr
	);

	this->editorWindow = std::make_unique<Window>(hInstance, _mainWindow);

	this->editor = std::make_unique<RenderWindow>(*this->editorWindow.get());
	_handleRenderWindow = reinterpret_cast<HWND>(this->editor->Window->NativeHandle());

	ShowWindow(_mainWindow, SW_MAXIMIZE);
}

void EditorWindow::Run()
{
	while (_running)
	{
		this->editor->RunOneFrame();
	}
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
				{
					char filebuff[_MAX_PATH]{};

					OPENFILENAMEA ofn{};
					ofn.lStructSize = sizeof(OPENFILENAMEA);
					ofn.hwndOwner = gEditorWindow->_mainWindow;
					ofn.lpstrTitle = "Open a 3DRadSpace project...";
					ofn.lpstrFile = filebuff;
					ofn.nMaxFile = _MAX_PATH;
					ofn.lpstrFilter = "3DRadSpace Project(*.3drsp)\0*.3drsp\0All Files(*.*)\0*.*";
					ofn.hInstance = gEditorWindow->_hInstance;
					
					if (GetOpenFileNameA(&ofn))
					{
						//open project file.
					}
					if(GetLastError() != 0)
						MessageBoxA(gEditorWindow->_mainWindow, std::format("Error trying to create the open file dialog box! : {}", GetLastError()).c_str(), "Test", MB_OK | MB_ICONWARNING);
					break;
				}
				case CMD_OpenRecentFile1:
					break;
				case CMD_OpenRecentFile1 + 1:
					break;
				case CMD_OpenRecentFile1 + 2:
					break;
				case CMD_OpenRecentFile1 + 3:
					break;
				case CMD_OpenRecentFile1 + 4:
					break;
				case CMD_OpenRecentFile1 + 5:
					break;
				case CMD_OpenRecentFile1 + 6:
					break;
				case CMD_OpenRecentFile1 + 7:
					break;
				case CMD_OpenRecentFile1 + 8:
					break;
				case CMD_OpenRecentFile1 + 9:
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
					ShellExecuteA(gEditorWindow->_mainWindow, nullptr, "https://3dradspace.com/Documentation", nullptr, nullptr, SW_NORMAL);
					break;
				case CMD_Homepage:
					ShellExecuteA(gEditorWindow->_mainWindow, nullptr, "https://3dradspace.com", nullptr, nullptr, SW_NORMAL);
					break;
				case CMD_Github:
					ShellExecuteA(gEditorWindow->_mainWindow, nullptr, "https://github.com/3DRadSpace/3D_Rad_Space/", nullptr, nullptr, SW_NORMAL);
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
			GetWindowRect(gEditorWindow->_toolbar, &rcToolbar);
			int toolbarHeight = rcToolbar.bottom - rcToolbar.top;

			SetWindowPos(gEditorWindow->_listBox, nullptr, 0, toolbarHeight + 1, 150, wndHeight - toolbarHeight, 0);
			SetWindowPos(gEditorWindow->_toolbar, nullptr, 0, 0, wndWidth, 25, 0);
			SetWindowPos(gEditorWindow->_handleRenderWindow, nullptr, 150, toolbarHeight, wndWidth - 150, wndHeight - toolbarHeight, 0);
			break;
		}
		default: break;
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}