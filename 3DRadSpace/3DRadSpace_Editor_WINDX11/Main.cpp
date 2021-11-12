#include "Main.h"

HWND MainWindow, RenderWindow, ToolBarWindow,ObjectsListBox;

HINSTANCE hGlobCurrentInst;

__stdstring CurrentFile(TEXT(""));

const wchar_t* const MainWindowClassName = TEXT("3DRADSPACE_MAIN_WINDOW");
const wchar_t* const EditorWindowClassName = TEXT("3DRADSPACE_EDITOR_WINDOW");

Vector3 _3DCursor(0, 0, 0) , CameraPos(5,5,5);
bool _3DMode = true, IsSaved = true, ShouldExit = false;

//Matrix View, Projection;
DirectX::XMMATRIX View, Projection;

std::unique_ptr<DirectX::Mouse> ptrMouse = std::make_unique<DirectX::Mouse>();
Point pMouseDelta;
float camRotX = 0.5, camRotY = -0.5;
float camZoom = 5;

std::unique_ptr<DirectX::CommonStates> CommonStates;
std::unique_ptr<DirectX::BasicEffect> BasicEffect;
std::unique_ptr < DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> AxisPrimitive;

std::vector<IObject*> IObjectList;

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
	AppendMenuW(FileMenu, MF_STRING, MENU_NEWFILE, TEXT("New project (Ctrl+N)"));
	AppendMenuW(FileMenu, MF_STRING, MENU_OPENFILE, TEXT("Open project (Ctrl+O)"));
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILE, TEXT("Save project (Ctrl+S)"));
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILEAS, TEXT("Save project as (Ctrl+Shift+S)"));
	AppendMenuW(FileMenu, MF_STRING, MENU_PLAYPROJECT, TEXT("Play project (Ctrl+P)"));
	AppendMenuW(FileMenu, MF_STRING, MENU_COMPILEPROJECT, TEXT("Build project (Ctrl+Shift+B)"));
	AppendMenuW(FileMenu, MF_STRING, MENU_EXIT, TEXT("Exit (Alt+F4)"));
	
	HMENU ObjectMenu = CreateMenu();
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDOBJ, TEXT("Add object (Ctrl+A)"));
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDPROJECT, TEXT("Add a addon"));
	AppendMenuW(ObjectMenu, MF_STRING, MENU_IMPORTRESOURCES, TEXT("Import resources"));
	AppendMenuW(ObjectMenu, MF_STRING, MENU_RESETCURSOR, TEXT("Reset 3D Cursor"));

	HMENU OptionsMenu = CreateMenu();
	AppendMenuW(OptionsMenu, MF_STRING, MENU_UPDATECHECK, TEXT("Check for updates..."));
	AppendMenuW(OptionsMenu, MF_STRING, MENU_PREFERENCES, TEXT("Preferences"));

	HMENU HelpMenu = CreateMenu();
	AppendMenuW(HelpMenu, MF_STRING, MENU_ABOUT, TEXT("About"));
	AppendMenuW(HelpMenu, MF_STRING, MENU_DOCS, TEXT("Documentation"));
	AppendMenuW(HelpMenu, MF_STRING, MENU_HOMEPAGE, TEXT("Homepage"));
	AppendMenuW(HelpMenu, MF_STRING, MENU_FORUM, TEXT("Forum"));
	AppendMenuW(HelpMenu, MF_STRING, MENU_GITHUB, TEXT("GitHub"));

	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)FileMenu, TEXT("File"));
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)ObjectMenu, TEXT("Edit"));
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)OptionsMenu, TEXT("Options"));
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)HelpMenu, TEXT("Help"));

	//create windows
	MainWindow = CreateWindowEx(0, MainWindowClassName, TEXT("3DRadSpace - Editor"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 925, 600, nullptr, MainMenu, hInstance, 0);
	RenderWindow = CreateWindowExW(0, EditorWindowClassName, TEXT("not used"), WS_CHILD, 125, 25, 800, 600, MainWindow, nullptr, hInstance, 0);

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
		{0,MENU_NEWFILE,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)TEXT("New")},
		{1,MENU_OPENFILE,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)TEXT("Open")},
		{2,MENU_SAVEFILE,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)TEXT("Save")},
		{3,MENU_PLAYPROJECT,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)TEXT("Play")},
		{4,MENU_COMPILEPROJECT,TBSTATE_ENABLED,BTNS_AUTOSIZE,{0},0,(INT_PTR)TEXT("Compile")},
		{5,MENU_SWITCH3D2D,TBSTATE_ENABLED,BTNS_CHECK | BTNS_AUTOSIZE,{0},0,(INT_PTR)TEXT("Switch 2D/3D")},
	};
	SendMessage(ToolBarWindow, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(ToolBarWindow, TB_ADDBUTTONS, (WPARAM)6, (LPARAM)&toolBarButtons);
	SendMessage(ToolBarWindow, TB_AUTOSIZE, 0, 0);

	/*
	Create a listbox.
	*/
	
	ObjectsListBox = CreateWindow(TEXT("SysTreeView32"), TEXT("not used"), WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 0, 0, 150, 600, MainWindow, nullptr, hInstance, nullptr);
	SetWindowLong(ObjectsListBox, GWL_ID, TVS_CHECKBOXES);

	//Show windows
	ShowWindow(MainWindow, SW_SHOWMAXIMIZED);
	ShowWindow(RenderWindow, SW_NORMAL);
	ShowWindow(ToolBarWindow, SW_SHOWMAXIMIZED);
	ShowWindow(ObjectsListBox, SW_NORMAL);
	ResizeWindows();

	Point resolution = GetDisplaySize();
	Point screenCenter = resolution * 0.5f;

	Game game(RenderWindow, Point(800,600));
	ID3D11Device* device = game.GetDevice();

	if (device == nullptr)
	{
		MessageBox(MainWindow, TEXT("Failed to create the ID3D11GraphicsDevice instance. The program cannot proceed."), TEXT("Fatal error!"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	ID3D11DeviceContext* context = game.GetDeviceContext();
	IDXGISwapChain* swapchain = game.GetSwapChain();

	View = DirectX::XMMatrixLookAtRH({ CameraPos.X,CameraPos.Y,CameraPos.Z }, { _3DCursor.X,_3DCursor.Y,_3DCursor.Z }, { 0.0f,1.0f,0.0f });
	Projection = DirectX::XMMatrixPerspectiveFovRH(Math::ToRadians(65.0f), (float)(resolution.X / resolution.Y), 0.001f, 500.0f);

	HRESULT r = 0;

	CommonStates = std::make_unique<DirectX::CommonStates>(device);
	BasicEffect = std::make_unique<DirectX::BasicEffect>(device);
	BasicEffect->SetVertexColorEnabled(true);
	BasicEffect->SetProjection(Projection);

	ID3D11InputLayout* colorured_line_inputlayout;
	
	r = DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(device, BasicEffect.get(), &colorured_line_inputlayout);
	if (FAILED(r))
	{
		MessageBox(MainWindow, TEXT("Failed to create a ID3D11InputLayout!"), TEXT("Runtime error"), MB_OK | MB_ICONERROR);
		return -1;
	}

	AxisPrimitive = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);

	
	StencilState stencil(&game);
	game.SetStencilState(&stencil);

	StartDiscordPresence();

	ptrMouse->SetWindow(RenderWindow);
	pMouseDelta = { 0,0 };

	std::chrono::duration<double,std::ratio<1,1>> update_dt, draw_dt;

	MSG m = { 0 };
	while (!ShouldExit)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		//WINAPI message handing
		while(PeekMessage(&m,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&m);
			DispatchMessageW(&m);
		}
		//update part

		DirectX::Mouse::State mouse = ptrMouse->GetState();

		HWND focusWindow = GetActiveWindow();

		Quaternion q;

		if (mouse.leftButton && (focusWindow == MainWindow || focusWindow == RenderWindow))
		{
			ptrMouse->SetVisible(false);
			pMouseDelta = screenCenter - Point(mouse.x, mouse.y);
			
			RECT r = { 0 };
			GetWindowRect(RenderWindow, &r);
			SetCursorPos(screenCenter.X + r.left, screenCenter.Y + r.top);

			camRotX -= pMouseDelta.X * 0.001f;
			camRotY += pMouseDelta.Y * 0.001f;
		}
		else
		{
			ptrMouse->SetVisible(true);
		}
		
		q = Quaternion::CreateFromYawPitchRoll(camRotX, 0, 0) * Quaternion::CreateFromYawPitchRoll(0, camRotY, 0);
		camZoom = 5 - mouse.scrollWheelValue * 0.01f;

		CameraPos = camZoom * Vector3::Transform(Vector3::UnitZ(), q);
		View = DirectX::XMMatrixLookAtRH({ CameraPos.X,CameraPos.Y,CameraPos.Z }, { _3DCursor.X,_3DCursor.Y,_3DCursor.Z }, { 0.0f,1.0f,0.0f });

		
		auto time2 = std::chrono::high_resolution_clock::now();

		update_dt = time2 - time1;

		auto time3 = std::chrono::high_resolution_clock::now();

		game.Clear({ 0,0,0,1 });

		Viewport Viewport(&game);
		Viewport.SetViewport(context);
		
		context->OMSetBlendState(CommonStates->Opaque(), nullptr, 0xFFFFFFFF);
		context->OMSetDepthStencilState(CommonStates->DepthNone(), 0);
		context->RSSetState(CommonStates->CullNone());
		BasicEffect->SetWorld(DirectX::XMMatrixTranslation(_3DCursor.X,_3DCursor.Y,_3DCursor.Z));
		BasicEffect->SetView(View); //the grid is going to be moved along with the selectioned object, this is desired
		context->IASetInputLayout(colorured_line_inputlayout);

		BasicEffect->Apply(context);
		AxisPrimitive->Begin();
		
		Vector3 directions[] = { 500 * Vector3::UnitX(),500 * Vector3::UnitY(),500 * Vector3::UnitZ() };
		ColorShader colours[] = { {1,0,0,1},{0,1,0,1},{0,0,1,1} };
		DirectX::XMVECTOR vc_white{ 1,1,1,1 }, vc_gray{ 0.5f,0.5f,0.5f,1 };
		DirectX::XMVECTOR nullpos{ 0,0,0 };

		for (int i = 0; i <= 20; i++)
		{
			if (i == 10) continue;

			//x aglines gray lines
			AxisPrimitive->DrawLine(DirectX::VertexPositionColor({ -10.f,0, 10.f - i }, vc_gray),
				DirectX::VertexPositionColor({ 10.f,0,10.f - i }, vc_gray));

			//y aglines gray lines

			AxisPrimitive->DrawLine(DirectX::VertexPositionColor({-10.f +i,0,10.f},vc_gray),
				DirectX::VertexPositionColor({-10.f + i,0,-10.f},vc_gray));
		}
		//the 3 coloured axis indicating the X,Y,Z vectors
		//x - red
		//y - greed
		//z - blue
		for (size_t i = 0; i < 3; i++)
		{
			DirectX::XMVECTOR vcolor = { colours[i].R,colours[i].G,colours[i].B,colours[i].A };

			AxisPrimitive->DrawLine(DirectX::VertexPositionColor(nullpos,vcolor),
				DirectX::VertexPositionColor({ directions[i].X,directions[i].Y,directions[i].Z }, vcolor));

			AxisPrimitive->DrawLine(DirectX::VertexPositionColor(nullpos, vc_white),
				DirectX::VertexPositionColor({ -directions[i].X,-directions[i].Y,-directions[i].Z }, vc_white));
		}

		AxisPrimitive->End();

		game.Present();

		auto time4 = std::chrono::high_resolution_clock::now();
		draw_dt = time4 - time3;
	}
	colorured_line_inputlayout->Release();
	delete AxisPrimitive.release();
	delete BasicEffect.release();
	delete CommonStates.release();

#if _DEBUG
	IDXGIDebug* debugDev;
	HRESULT hr = DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debugDev));
	debugDev->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
	debugDev->Release();
#endif
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
		case WM_QUIT:
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
					lstrcatW(projPath, TEXT("\\Projects\\"));

					wchar_t filePath[MAX_PATH+1];
					memset(filePath, 0, sizeof(filePath));

					OPENFILENAME ofn;
					memset(&ofn, 0, sizeof(ofn));
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = MainWindow;
					ofn.lpstrFilter = __3DRADSPACE_FD_FILTER;
					ofn.lpstrTitle = TEXT("Open a project...");
					ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
					ofn.lpstrInitialDir = projPath;
					ofn.lpstrFile = filePath;
					ofn.hInstance = hGlobCurrentInst;
					ofn.nMaxFile = MAX_PATH;
					if (GetOpenFileName(&ofn))
					{
						filePath[MAX_PATH] = 0; 
						CurrentFile = filePath;
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
					ShellExecute(nullptr, nullptr, TEXT("http://3dradspace.com/Documentation/index.html"), nullptr, nullptr, 0);
					break;
				}
				case MENU_HOMEPAGE:
				{
					ShellExecute(nullptr, nullptr, TEXT("http://3dradspace.com"),nullptr,nullptr,0);
					break;
				}
				case MENU_FORUM:
				{
					ShellExecute(nullptr, nullptr, TEXT("http://3dradspace.com/Forum"),nullptr,nullptr,0);
					break;
				}
				case MENU_GITHUB:
				{
					ShellExecute(nullptr, nullptr, TEXT("https://github.com/3DRadSpace/3D_Rad_Space/"), nullptr, nullptr, 0);
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
		case WM_ACTIVATEAPP:
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEHOVER:
		{
			DirectX::Mouse::ProcessMessage(msg, wParam, lParam);
			DirectX::Keyboard::ProcessMessage(msg, wParam, lParam);
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

	SetWindowPos(RenderWindow, nullptr, 150, toolbarheight, width, height - toolbarheight, SWP_SHOWWINDOW);
	SetWindowPos(ObjectsListBox, nullptr, 0, toolbarheight, 150, height - toolbarheight, SWP_SHOWWINDOW);
}

void CheckUpdate()
{
	HRESULT r = URLDownloadToFile(nullptr, TEXT("http://3dradspace.com/UpdateInfo/LastestVersion.txt"), TEXT("version.txt"), 0, nullptr);
	if (r == INET_E_DOWNLOAD_FAILURE)
	{
		int d = MessageBox(nullptr, TEXT("Cannot check the lastest version. Check your internet connection."), TEXT("Network error"), MB_RETRYCANCEL | MB_ICONWARNING);
		if (d == IDRETRY) CheckUpdate();
	}
	if (r == E_OUTOFMEMORY)
	{
		MessageBox(nullptr, TEXT("Cannot download a temporary file. Please try cleaning up some space from your drive."), TEXT("Out of memory"), MB_OK | MB_ICONERROR);
	}

	char buffer[255];
	memset(buffer, 0, 255);

	char version_online[10];
	memset(version_online, 0, 10);

	char* context = nullptr;
	std::ifstream read_update_info(TEXT("version.txt"));
	read_update_info.getline(buffer, 255);

	char* p = strtok_s(buffer, " ",&context);
	
	read_update_info.close();

	DeleteFile(TEXT("version.txt"));

	int i = 0;
	while (p)
	{
		if (strcmp(p, __3DRADSPACE_VERSION) == 0)
		{
			MessageBox(nullptr, TEXT("No new update found!"), TEXT("Update check"), MB_OK | MB_ICONINFORMATION);
			return;
		}
		else if( i == 0)
		{
			strcpy_s<10>(version_online, p);
			p = strtok_s(nullptr, " ", &context);
			i += 1;
			continue;
		}
		if (strstr(p, "http://") != nullptr)
		{
			int mr = MessageBox(nullptr, TEXT("A new update was found! Do you want it to be downloaded and installed?"), TEXT("Update check"), MB_YESNO | MB_ICONQUESTION);
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
		int m = MessageBox(nullptr, TEXT("This project is not saved. Unsaved progress may be lost. Save project?"), TEXT("Project not saved"), MB_YESNOCANCEL | MB_ICONWARNING);
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
	if (CurrentFile == TEXT("")) SaveProjectAs();
	else
	{
		IsSaved = true;
		//...
	}
}
void SaveProjectAs()
{
	if (CurrentFile != TEXT("")) SaveProject();
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

Point GetRenderWindowResolution()
{
	RECT r = { 0 };
	GetWindowRect(MainWindow, &r);
	int width = r.right - r.left;
	int height = r.bottom - r.top;

	return Point(width,height);
}

Point GetDisplaySize()
{
	HMONITOR monitor = MonitorFromWindow(MainWindow, MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	memset(&info, 0, sizeof(MONITORINFO));
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
	int monitor_width = info.rcMonitor.right - info.rcMonitor.left;
	int monitor_height = info.rcMonitor.bottom - info.rcMonitor.top;
	return Point(monitor_width, monitor_height);
}

void __cdecl LostGDevice()
{
	SaveProject();
	MessageBox(MainWindow, TEXT("Lost the graphics device."), TEXT("Fatal error!"), MB_OK | MB_ICONERROR);
	ExitEditor();
}

//We need an array for the tree view items apparently
void AddObject(IObject* object)
{
	TVITEM tree_view_item;
	memset(&tree_view_item, 0, sizeof(TVITEM));
	tree_view_item.mask = TVIF_TEXT | TVIF_PARAM;
	//UNICODE and non-UNICODE compatibility
#ifdef UNICODE
	wchar_t objname[255];
	size_t num_chr_conv = 0;
	mbstowcs_s<255>(&num_chr_conv, objname, object->Name.c_str(), 255);
	tree_view_item.pszText = objname;
	tree_view_item.cchTextMax = num_chr_conv;
#else
	tree_view_item.pszText = object->Name.c_str();
	tree_view_item.cchTextMax = object->Name.size();
#endif
	tree_view_item.lParam = 0;

	TVINSERTSTRUCT tv_ins;
	memset(&tv_ins, 0, sizeof(TVINSERTSTRUCT));
	tv_ins.hInsertAfter = nullptr; //TODO: variable with the last element. we need a global variable
	tv_ins.hParent = TVI_ROOT;
	tv_ins.item = tree_view_item;

	HTREEITEM CurrItem = (HTREEITEM)SendMessage(ObjectsListBox, TVM_INSERTITEM,
		0, (LPARAM)(LPTVINSERTSTRUCT)&tv_ins);

	//add CurrItem to the list of handles
}

void RemoveObject(size_t index)
{
	SendMessage(ObjectsListBox, TVM_DELETEITEM,0x0, 0x420); // TODO CHANGE 420 to an element in the array
}

void RefresObjectList()
{
	for (size_t i = 0; i < 420; i++)
	{
		//TODO: remove i-th object
	}

	for (size_t i = 0; i < IObjectList.size(); i++)
	{
		AddObject(IObjectList[i]);
	}
}
