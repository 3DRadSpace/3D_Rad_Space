#include "Main.h"

HWND MainWindow, RenderWindow, ToolBarWindow;

HINSTANCE hGlobCurrentInst;

std::wstring CurrentFile(L"");

const wchar_t* const MainWindowClassName = L"3DRADSPACE_MAIN_WINDOW";
const wchar_t* const EditorWindowClassName = L"3DRADSPACE_EDITOR_WINDOW";

Vector3 _3DCursor(0, 0, 0);
bool _3DMode = true, IsSaved = true, ShouldExit = false;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_  PWSTR args, _In_  int nShowCmd)
{
	//set current directory
	wchar_t currPath[MAX_PATH];
	GetModuleFileName(nullptr, currPath, MAX_PATH);
	PathCchRemoveFileSpec(currPath, MAX_PATH);
	SetCurrentDirectory(currPath);

	//load editor icon
	HICON hAppIcon = static_cast<HICON>(::LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, LR_DEFAULTCOLOR));
	
	//Register editor class
	WNDCLASS wndclass;
	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.lpfnWndProc = WindowProcessMain;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = MainWindowClassName;
	wndclass.hIcon = hAppIcon;

	RegisterClass(&wndclass);

	//Register 3D window class
	WNDCLASS editorwndclass;
	memset(&editorwndclass, 0, sizeof(WNDCLASS));
	editorwndclass.lpfnWndProc = WindowProcessEditor;
	editorwndclass.hInstance = hInstance;
	editorwndclass.lpszClassName = EditorWindowClassName;

	RegisterClass(&editorwndclass);
	/*
		Create Menu control
	*/
	HMENU MainMenu = CreateMenu();
	
	HMENU FileMenu = CreateMenu();
	AppendMenuW(FileMenu, MF_STRING, MENU_NEWFILE, L"New project (Ctrl+N)");
	AppendMenuW(FileMenu, MF_STRING, MENU_OPENFILE, L"Open project (Ctrl+O)");
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILE, L"Save project (Ctrl+S)");
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILEAS, L"Save project as (Ctrl+Shift+S)");
	AppendMenuW(FileMenu, MF_STRING, MENU_PLAYPROJECT, L"Play project (Ctrl+P)");
	AppendMenuW(FileMenu, MF_STRING, MENU_COMPILEPROJECT, L"Build project (Ctrl+Shift+B)");
	AppendMenuW(FileMenu, MF_STRING, MENU_EXIT, L"Exit (Alt+F4)");
	
	HMENU ObjectMenu = CreateMenu();
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDOBJ, L"Add object (Ctrl+A)");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDPROJECT, L"Add a addon");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_IMPORTRESOURCES, L"Import resources");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_RESETCURSOR, L"Reset 3D Cursor");

	HMENU OptionsMenu = CreateMenu();
	AppendMenuW(OptionsMenu, MF_STRING, MENU_UPDATECHECK, L"Check for updates...");
	AppendMenuW(OptionsMenu, MF_STRING, MENU_PREFERENCES, L"Preferences");

	HMENU HelpMenu = CreateMenu();
	AppendMenuW(HelpMenu, MF_STRING, MENU_ABOUT, L"About");
	AppendMenuW(HelpMenu, MF_STRING, MENU_DOCS, L"Documentation");
	AppendMenuW(HelpMenu, MF_STRING, MENU_HOMEPAGE, L"Homepage");
	AppendMenuW(HelpMenu, MF_STRING, MENU_FORUM, L"Forum");
	AppendMenuW(HelpMenu, MF_STRING, MENU_GITHUB, L"GitHub");

	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)FileMenu, L"File");
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)ObjectMenu, L"Edit");
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)OptionsMenu, L"Options");
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)HelpMenu, L"Help");

	//create windows
	MainWindow = CreateWindowEx(0, MainWindowClassName, L"3DRadSpace - Editor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 600, nullptr, MainMenu, hInstance, 0);
	RenderWindow = CreateWindowExW(0, EditorWindowClassName, L"not used", WS_CHILD, 0, 25, 800, 600, MainWindow, nullptr, hInstance, 0);

	/*
		Create toolbar with an image list
	*/

	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX) , ICC_BAR_CLASSES };
	InitCommonControlsEx(&icc);

	HIMAGELIST toolBarImageList = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 6, 0);
	ImageList_AddIcon(toolBarImageList, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2)));
	ImageList_AddIcon(toolBarImageList, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON3)));
	ImageList_AddIcon(toolBarImageList, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON4)));
	ImageList_AddIcon(toolBarImageList, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON5)));
	ImageList_AddIcon(toolBarImageList, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON6)));
	ImageList_AddIcon(toolBarImageList, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON7)));

	ToolBarWindow = CreateWindowEx(0, TOOLBARCLASSNAME, nullptr, WS_CHILD | TBSTYLE_LIST, 0, 0, 0, 0,MainWindow, nullptr, hInstance, nullptr);
	SendMessage(ToolBarWindow, TB_SETIMAGELIST, 0, (LPARAM)toolBarImageList);
	SendMessage(ToolBarWindow, TB_LOADIMAGES, 0, (LPARAM)HINST_COMMCTRL);
	
	TBBUTTON toolBarButtons[6] =
	{
		{0,MENU_NEWFILE,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)L"New"},
		{1,MENU_OPENFILE,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)L"Open"},
		{2,MENU_SAVEFILE,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)L"Save"},
		{3,MENU_PLAYPROJECT,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)L"Play"},
		{4,MENU_COMPILEPROJECT,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)L"Compile"},
		{5,MENU_SWITCH3D2D,TBSTATE_ENABLED,BTNS_CHECK | BTNS_AUTOSIZE,{0},0,(INT_PTR)L"Switch 2D/3D"},
	};
	SendMessage(ToolBarWindow, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(ToolBarWindow, TB_ADDBUTTONS, (WPARAM)6, (LPARAM)&toolBarButtons);
	SendMessage(ToolBarWindow, TB_AUTOSIZE, 0, 0);

	//Show windows
	ShowWindow(MainWindow, SW_SHOWMAXIMIZED);
	ShowWindow(RenderWindow, SW_NORMAL);
	ShowWindow(ToolBarWindow, SW_SHOWMAXIMIZED);
	ResizeWindows();

	Game game(RenderWindow);
	ID3D11Device* device = game.GetDevice();
	ID3D11DeviceContext* context = game.GetDeviceContext();
	IDXGISwapChain* swapchain = game.GetSwapChain();

	HRESULT r = 0;

	StencilState stencil(&game);
	game.SetStencilState(&stencil);

	//Basic coloured triangle test code. Will be removed in the future.
	VertexPositionColorDeclaration *Triangles = new VertexPositionColorDeclaration[3]; //use heap memory since we call delete[] in the destructor
	Triangles[0] = { {0.0f,  0.5f,  0.0f,1.0f},{1.0f,0,0,1.0f} };
	Triangles[1] = { {0.5f,  -0.5f,  0.0f,1.0f},{0.0f,1.0f,0,1.0f} };
	Triangles[2] = { {-0.5f,  -0.5f,  0.0f,1.0f},{0.0f,0,1.0f,1.0f} };

	VertexBuffer<VertexPositionColorDeclaration> TestTriangle(Triangles, 3);
	TestTriangle.CreateVertexBuffer(device);

	Shader SimpleVertexShader(ShaderType::Vertex);
	SimpleVertexShader.LoadFromFile(L"VS_NoTransform_PositionColor.hlsl", "basic_vs");
	SimpleVertexShader.CompileShader(device);

	Shader SimplePixelShader(ShaderType::Pixel);
	SimplePixelShader.LoadFromFile(L"VS_NoTransform_PositionColor.hlsl", "basic_ps");
	SimplePixelShader.CompileShader(device);

	SamplerState SamplerState(device);
	SamplerState.SetSamplerVertexShader(context);
	SamplerState.SetSamplerPixelShader(context);

	RasterizerState RasterizerState(device);
	RasterizerState.SetRasterizerState(context);

	ShaderInputLayout inputlayout({ InputLayoutElement::Position,InputLayoutElement::Color });
	inputlayout.CreateInputLayout(device, &SimpleVertexShader);

	StartDiscordPresence();

	MSG m = { 0 };
	while (!ShouldExit)
	{
		while(PeekMessage(&m,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&m);
			DispatchMessageW(&m);
		}

		game.Clear({ 0,0,0,1 });

		Viewport Viewport;
		Viewport.SetViewport(context);
		
		inputlayout.SetInputLayout(context);
		SimpleVertexShader.SetShader(context);
		SimplePixelShader.SetShader(context);
		
		game.SetTopology(PrimitiveTopology::TriangleList);
		TestTriangle.Draw(context);

		game.Present();

	}
	return 0;
}

LRESULT __stdcall WindowProcessMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			ExitEditor();
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT sPaint;
			HDC h = BeginPaint(MainWindow, &sPaint);
			FillRect(h, &sPaint.rcPaint, CreateSolidBrush(RGB(255,255,255)));
			EndPaint(MainWindow, &sPaint);
			break;
		}
		case WM_SIZE:
		{
			ResizeWindows();
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case MENU_NEWFILE:
				{
					if(ShowProjectNotSavedWarning())
						ResetLoadedProject();
					break;
				}
				case MENU_OPENFILE:
				{
					if (!ShowProjectNotSavedWarning()) break;
					wchar_t projPath[MAX_PATH];
					GetModuleFileName(nullptr, projPath, MAX_PATH);
					PathCchRemoveFileSpec(projPath, MAX_PATH);
					lstrcatW(projPath, L"\\Projects\\");

					wchar_t filePath[MAX_PATH+1];
					memset(filePath, 0, sizeof(filePath));

					OPENFILENAME ofn;
					memset(&ofn, 0, sizeof(ofn));
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = MainWindow;
					ofn.lpstrFilter = __3DRADSPACE_FD_FILTER;
					ofn.lpstrTitle = L"Open a project...";
					ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
					ofn.lpstrInitialDir = projPath;
					ofn.lpstrFile = filePath;
					ofn.hInstance = hGlobCurrentInst;
					ofn.nMaxFile = MAX_PATH;
					if (GetOpenFileName(&ofn))
					{
						filePath[MAX_PATH] = 0; // STFU C6054
						CurrentFile = filePath; //C6504 is useless, stfu Intellisense:tm:
						UpdateDiscordRichPresence();
						IsSaved = true;
					}
					break;
				}
				case MENU_SAVEFILE:
				{
					SaveProject();
					break;
				}
				case MENU_SAVEFILEAS:
				{
					SaveProjectAs();
					break;
				}
				case MENU_PLAYPROJECT:
					break;
				case MENU_COMPILEPROJECT:
					break;
				case MENU_EXIT:
				{
					ExitEditor();
					break;
				}
				case MENU_ADDOBJ:
				{
					break;
				}
				case MENU_ADDPROJECT:
				{
					break;
				}
				case MENU_IMPORTRESOURCES:
				{
					break;
				}
				case MENU_RESETCURSOR:
				{
					_3DCursor = Vector3::Zero();
					break;
				}
				case MENU_UPDATECHECK:
				{
					CheckUpdate();
					break;
				}
				case MENU_PREFERENCES:
				{
					break;
				}
				case MENU_ABOUT:
				{
					break;
				}
				case MENU_DOCS:
				{
					ShellExecute(nullptr, nullptr, L"https://3dradspace.com/Documentation/index.html", nullptr, nullptr, 0);
					break;
				}
				case MENU_HOMEPAGE:
				{
					ShellExecute(nullptr, nullptr, L"https://3dradspace.com",nullptr,nullptr,0);
					break;
				}
				case MENU_FORUM:
				{
					ShellExecute(nullptr, nullptr, L"https://3dradspace.com/Forum",nullptr,nullptr,0);
					break;
				}
				case MENU_GITHUB:
				{
					ShellExecute(nullptr, nullptr, L"https://github.com/3DRadSpace/3D_Rad_Space/", nullptr, nullptr, 0);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	return DefWindowProcW(hwnd,msg,wParam,lParam);
}

LRESULT __stdcall WindowProcessEditor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			ExitEditor();
			break;
		}
		default: break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void ResizeWindows()
{
	RECT r = { 0 };
	GetWindowRect(MainWindow,&r);
	int width = r.right - r.left;
	int height = r.bottom - r.top;

	GetWindowRect(ToolBarWindow, &r);
	int toolbarheight = r.bottom - r.top;

	SetWindowPos(RenderWindow, nullptr, 0, toolbarheight, width, height - toolbarheight, SWP_SHOWWINDOW);
}

void CheckUpdate()
{
	HRESULT r = URLDownloadToFile(nullptr, L"https://3dradspace.com/UpdateInfo/LastestVersion.txt", L"version.txt", 0, nullptr);
	if (r == INET_E_DOWNLOAD_FAILURE)
	{
		int d = MessageBox(nullptr, L"Cannot check the lastest version. Check your internet connection.", L"Network error", MB_RETRYCANCEL | MB_ICONWARNING);
		if (d == IDRETRY) CheckUpdate();
	}
	if (r == E_OUTOFMEMORY)
	{
		MessageBox(nullptr, L"Cannot download a temporary file. Please try cleaning up some space from your drive.", L"Out of memory", MB_OK | MB_ICONERROR);
	}

	char buffer[255];
	memset(buffer, 0, 255);

	char version_online[10];
	memset(version_online, 0, 10);

	char* context = nullptr;
	std::ifstream read_update_info(L"version.txt");
	read_update_info.getline(buffer, 255);

	char* p = strtok_s(buffer, " ",&context);
	
	read_update_info.close();

	DeleteFile(L"version.txt");

	int i = 0;
	while (p)
	{
		if (strcmp(p, __3DRADSPACE_VERSION) == 0)
		{
			MessageBox(nullptr, L"No new update found!", L"Update check", MB_OK | MB_ICONINFORMATION);
			return;
		}
		else if( i == 0)
		{
			strcpy_s<10>(version_online, p);
			p = strtok_s(nullptr, " ", &context);
			i += 1;
			continue;
		}
		if (strstr(p, "https://") != nullptr)
		{
			int mr = MessageBox(nullptr, L"A new update was found! Do you want it to be downloaded and installed?", L"Update check", MB_YESNO | MB_ICONQUESTION);
			if (mr == IDYES)
			{
				DownloadUpdate(p,version_online);
			}
		}
		p = strtok_s(nullptr, " ", &context);
	}

}

void DownloadUpdate(char* link,char* version)
{
	std::string file = "3DRadSpace v";
	file += version;
	file += " Setup.exe";

	std::string downloadlink = link;

	DownloadStatusWindow::Reset();

	UpdateDownloadManager m;

	std::thread downloadthread([](std::string link, std::string file,UpdateDownloadManager m) -> void
		{
			DownloadStatusWindow::SetManager(&m);
			HRESULT r = URLDownloadToFileA(nullptr, link.c_str(), file.c_str(), 0, &m);
		}
	,downloadlink,file,m);

	DownloadStatusWindow::Register(hGlobCurrentInst);
	DownloadStatusWindow::Create(nullptr);

	downloadthread.detach();

	if (DownloadStatusWindow::Finished && !DownloadStatusWindow::Cancelled)
	{
		ShellExecuteA(nullptr, nullptr, file.c_str(), nullptr, nullptr, 0);
		ExitEditor();
	}
}

void StartDiscordPresence()
{
	Discord_Initialize("612682115208708098", nullptr, 1, nullptr);

	DiscordRichPresence drp;
	memset(&drp, 0, sizeof(DiscordRichPresence));
	drp.startTimestamp = time(nullptr);
	drp.largeImageKey = "mainicon";
	drp.state = "New project";
	Discord_UpdatePresence(&drp);
}


void ResetLoadedProject()
{
	//reset internal data
	CurrentFile.erase();
	//<- reset object list

	DiscordRichPresence drp;
	memset(&drp, 0, sizeof(DiscordRichPresence));
	drp.startTimestamp = time(nullptr);
	drp.largeImageKey = "mainicon";
	drp.state = "New project";
	Discord_UpdatePresence(&drp);
	IsSaved = true;
}

bool ShowProjectNotSavedWarning()
{
	if (!IsSaved)
	{
		int m = MessageBox(nullptr, L"This project is not saved. Unsaved progress may be lost. Save project?", L"Project not saved", MB_YESNOCANCEL | MB_ICONWARNING);
		if (m == IDYES)
		{
			SaveProject();
			return true;
		}
		if (m == IDNO)
		{
			return true;
		}
		else return false;
	}
	return true;
}

void SaveProject()
{
	if (CurrentFile == L"") SaveProjectAs();
	else
	{
		IsSaved = true;
		//...
	}
}
void SaveProjectAs()
{
	if (CurrentFile != L"") SaveProject();
	wchar_t filebuffer[MAX_PATH+1];
	memset(filebuffer, 0, sizeof(filebuffer));

	OPENFILENAME sfn;
	memset(&sfn, 0, sizeof(sfn));
	sfn.lStructSize = sizeof(sfn);
	sfn.hwndOwner = MainWindow;
	sfn.lpstrFilter = __3DRADSPACE_FD_FILTER;
	sfn.hInstance = hGlobCurrentInst;
	sfn.Flags = OFN_DONTADDTORECENT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	sfn.lpstrFile = filebuffer;
	sfn.nMaxFile = MAX_PATH;
	if (GetSaveFileName(&sfn))
	{
		filebuffer[MAX_PATH] = 0;
		CurrentFile = filebuffer;
		SaveProject();
	}
}

void UpdateDiscordRichPresence()
{
	DiscordRichPresence drp;
	memset(&drp, 0, sizeof(DiscordRichPresence));
	drp.startTimestamp = time(nullptr);
	drp.largeImageKey = "mainicon";
	drp.details = "Working on a project";

	size_t fileindex = CurrentFile.find_last_of('\\') + 1;
	size_t extension_index = CurrentFile.find_last_of('.');

	char filebuffer[MAX_PATH];
	memset(filebuffer, 0, sizeof(filebuffer));
	
	sprintf_s<MAX_PATH>(filebuffer,"%ws", CurrentFile.c_str() + fileindex);
	filebuffer[extension_index - fileindex] = 0;

	drp.state = filebuffer;
	Discord_UpdatePresence(&drp);
}

void StopDiscordRichPresence()
{
	Discord_ClearPresence();
	Discord_Shutdown();
}

void ExitEditor()
{
	if(!ShowProjectNotSavedWarning()) return;
	StopDiscordRichPresence();
	ShouldExit = true;
}
