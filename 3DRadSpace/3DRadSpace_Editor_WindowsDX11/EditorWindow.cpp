#include "EditorWindow.hpp"
#include "resource.h"
#include "Engine3DRadSpace/Error.hpp"
#include <fstream>
#include <CommCtrl.h>
#include "HelperFunctions.hpp"
#include <d3d11.h>
#include <assert.h>

#include "AddObjectDialog.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

EditorWindow* gEditorWindow = nullptr;

void EditorWindow::_saveProject(const char* filename)
{
	if (filename == nullptr)
	{
		char filebuff[_MAX_PATH]{};

		OPENFILENAMEA ofn{};
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = gEditorWindow->_mainWindow;
		ofn.lpstrTitle = "Save a 3DRadSpace project...";
		ofn.lpstrFile = filebuff;
		ofn.nMaxFile = _MAX_PATH;
		ofn.lpstrFilter = FileFilter;
		ofn.hInstance = gEditorWindow->_hInstance;

		if (GetSaveFileNameA(&ofn))
		{
			//save project at filename contained by filebuff
		}
		else if (GetLastError() != 0)
			MessageBoxA(gEditorWindow->_mainWindow, std::format("Error trying to create the save file dialog box! : {}", GetLastError()).c_str(), "Error!", MB_OK | MB_ICONWARNING);
	}
	else
	{
		//save project at filename
	}
}

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
	wndclass.hIcon = LoadIconA(hInstance,MAKEINTRESOURCEA(IDI_ICON1));

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
	for(int i = 0; recent_projects; i++)
	{
		std::string filename;
		std::getline(recent_projects, filename);
		AppendMenuA(recentProjectsMenu, MF_STRING, CMD_OpenRecentFile1 + static_cast<UINT_PTR>(i), filename.c_str());
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
	AppendMenuA(editMenu, MF_STRING, CMD_AddPrefab, "Add Prefab (Ctrl+Shift+A)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddAddon, "Add Addon");
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
	
	SendMessageA(_toolbar, TB_SETIMAGELIST, 0, (LPARAM)(toolbarImageList));
	SendMessageA(_toolbar, TB_LOADIMAGES, 0, (LPARAM)HINST_COMMCTRL);
	
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

	_listBox = CreateWindowExA(
		0,
		WC_TREEVIEWA,
		"",
		TVS_CHECKBOXES | WS_CHILD | WS_VISIBLE | WS_BORDER,
		0,
		0, 
		150,
		600,
		_mainWindow,
		nullptr,
		hInstance,
		nullptr
	);

	this->editor = std::make_unique<RenderWindow>(_mainWindow,_hInstance);

	_handleRenderWindow = static_cast<HWND>(this->editor->Window->NativeHandle());

	//Accelerator table
	acceleratorTable = LoadAcceleratorsA(hInstance, MAKEINTRESOURCEA(IDR_ACCELERATOR1));
	RaiseFatalErrorIfNull(acceleratorTable, "Failed to create the accelerator table");
	
	ShowWindow(_mainWindow, SW_MAXIMIZE);
	ShowWindow(_toolbar, SW_NORMAL);
	ShowWindow(_listBox, SW_NORMAL);
}

void EditorWindow::Run()
{
	//Modified code from Window::Run() so accelerators are also translated.
	this->editor->Initialize();

	double u_dt = 0;
	double d_dt = 0;
	while (true)
	{
		MSG msg;
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAcceleratorA(_mainWindow, acceleratorTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}
		if (!_running) break;
		if (!this->editor) continue;

		auto ts_u1 = std::chrono::steady_clock::now();
		editor->Update(editor->Window->GetKeyboardState(), editor->Window->GetMouseState(), u_dt);
		auto ts_u2 = std::chrono::steady_clock::now();

		std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
		u_dt = uDiff.count();

		auto ts_d1 = std::chrono::steady_clock::now();

		this->editor->Device->SetViewport(Viewport(RectangleF(0, 0, 800, 600), 0.0f, 1.0f));
		this->editor->Device->Clear({0, 0, 0, 1});
		this->editor->Draw(this->editor->View, this->editor->Projection, d_dt);
		this->editor->Device->Present();

		auto ts_d2 = std::chrono::steady_clock::now();

		std::chrono::duration<double> dDiff = ts_d2 - ts_d1;
		d_dt = dDiff.count();
	}
}

EditorWindow::~EditorWindow()
{
	DestroyWindow(this->_mainWindow);
}

LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps{};
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CLOSE:
		{
			gEditorWindow->_running = false;
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_QUIT:
		{
			exit(0);
		}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case CMD_NewFile:
				case ACC_NEW_PROJECT:
					break;
				case CMD_OpenFile:
				case ACC_OPEN_PROJECT:
				{
					char filebuff[_MAX_PATH]{};

					OPENFILENAMEA ofn{};
					ofn.lStructSize = sizeof(OPENFILENAMEA);
					ofn.hwndOwner = gEditorWindow->_mainWindow;
					ofn.lpstrTitle = "Open a 3DRadSpace project...";
					ofn.lpstrFile = filebuff;
					ofn.nMaxFile = _MAX_PATH;
					ofn.lpstrFilter = FileFilter;
					ofn.hInstance = gEditorWindow->_hInstance;

					if(GetOpenFileNameA(&ofn))
					{
						//open project file.
					}
					else if(GetLastError() != 0)
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
				case ACC_SAVE_PROJECT:
					gEditorWindow->_saveProject(gEditorWindow->_currentFile);
					break;
				case CMD_SaveProjectAs:
				case ACC_SAVE_PROJECT_AS:
					gEditorWindow->_saveProject(nullptr);
					break;
				case CMD_PlayProject:
				case ACC_PLAY_PROJECT:
					break;
				case CMD_BuildProject:
				case ACC_BUILD_PROJECT:
					break;
				case CMD_Exit:
					gEditorWindow->_running = false;
					break;
				case CMD_AddObject:
				case ACC_ADD_OBJECT:
				{
					AddObjectDialog dialog(hwnd, gEditorWindow->_hInstance);
					dialog.ShowDialog();
					break;
				}
				case CMD_AddAsset:
				case ACC_ADD_ASSET:
					break;
				case CMD_AddAddon:
				case ACC_ADD_PREFAB:
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
			GetClientRect(gEditorWindow->_toolbar, &rcToolbar);
			int toolbarHeight = rcToolbar.bottom - rcToolbar.top;

			SetWindowPos(gEditorWindow->_listBox, nullptr, 0, toolbarHeight, 150, wndHeight - toolbarHeight, 0);
			SetWindowPos(gEditorWindow->_toolbar, nullptr, 0, 0, wndWidth, 25, 0);
			SetWindowPos(gEditorWindow->_handleRenderWindow, nullptr, 150, toolbarHeight, wndWidth - 150, wndHeight - toolbarHeight, 0);
			break;
		}
		case WM_DROPFILES:
		{
			HDROP drop = reinterpret_cast<HDROP>(wParam);
			char file[_MAX_PATH];
			int numFilesDropped = DragQueryFileA(drop, 0xFFFFFFFF, nullptr, 0);

			for(int i = 0; i < numFilesDropped; i++)
			{
				DragQueryFileA(drop, i, file, _MAX_PATH);
				//handle dropped file
				//MessageBoxA(gEditorWindow->_mainWindow, file, "Dropped file", MB_ICONINFORMATION);
			}
			break;
		}
		default:
			break;
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}