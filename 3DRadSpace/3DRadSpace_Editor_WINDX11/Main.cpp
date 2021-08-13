#include "Main.h"
#include "resource.h"

HWND MainWindow, RenderWindow;

const wchar_t* const MainWindowClassName = L"3DRADSPACE_MAIN_WINDOW";
const wchar_t* const EditorWindowClassName = L"3DRADSPACE_EDITOR_WINDOW";

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR args, int nShowCmd)
{
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
	editorwndclass.hIcon = hAppIcon;

	RegisterClass(&editorwndclass);

	//Create main window menu
	HMENU MainMenu = CreateMenu();
	
	HMENU FileMenu = CreateMenu();
	AppendMenuW(FileMenu, MF_STRING, MENU_NEWFILE, L"New project (Ctrl+N)");
	AppendMenuW(FileMenu, MF_STRING, MENU_OPENFILE, L"Open project (Ctrl+O)");
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILE, L"Save project (Ctrl+S)");
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILEAS, L"Save project as (Ctrl+Shift+S)");
	AppendMenuW(FileMenu, MF_STRING, MENU_PLAYPROJECT, L"Play project (Ctrl+p)");
	AppendMenuW(FileMenu, MF_STRING, MENU_COMPILEPROJECT, L"Build project (Ctrl+Shift+B)");
	AppendMenuW(FileMenu, MF_STRING, MENU_EXIT, L"Exit (Alt+F4)");
	
	HMENU ObjectMenu = CreateMenu();
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDOBJ, L"Add object (Ctrl+A)");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDPROJECT, L"Add a addon");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_INSTALLFILES, L"Import resources");
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
	MainWindow = CreateWindowExW(0, MainWindowClassName, L"3DRadSpace - Editor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 600, nullptr, MainMenu, hInstance, 0);
	RenderWindow = CreateWindowExW(0, EditorWindowClassName, L"not used", WS_CHILD, 0, 0, 800, 600, MainWindow, nullptr, hInstance, 0);

	ShowWindow(MainWindow, SW_SHOWMAXIMIZED);
	ShowWindow(RenderWindow, SW_NORMAL);
	ResizeWindows();

	RS_DX11::Game game(RenderWindow);
	ID3D11Device* device = game.GetDevice();
	ID3D11DeviceContext* context = game.GetDeviceContext();
	IDXGISwapChain* swapchain = game.GetSwapChain();

	ID3D11Texture2D* backtexture = nullptr;
	HRESULT r = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backtexture);
	if (backtexture == nullptr)
	{
		MessageBox(nullptr, L"Failed to create the back buffer texture ID3D11Texture2D.", L"Fatal error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	ID3D11RenderTargetView* MainRenderTarget = nullptr;
	device->CreateRenderTargetView(backtexture, nullptr, &MainRenderTarget);
	backtexture->Release();
	
	if (MainRenderTarget == nullptr)
	{
		MessageBox(nullptr, L"Failed to create the main render target.", L"Fatal error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	ID3D11Texture2D* StencilTexture;
	D3D11_TEXTURE2D_DESC StencilTxtDesc;
	memset(&StencilTxtDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	StencilTxtDesc.ArraySize = 1;
	StencilTxtDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	StencilTxtDesc.MipLevels = 1;
	StencilTxtDesc.Width = 800;
	StencilTxtDesc.Height = 600;
	StencilTxtDesc.SampleDesc.Count = 1;
	StencilTxtDesc.SampleDesc.Quality = 0;
	StencilTxtDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

	device->CreateTexture2D(&StencilTxtDesc,nullptr,&StencilTexture);

	if (StencilTexture == nullptr)
	{
		MessageBox(nullptr, L"Failed to create the depth stencil texture.", L"Fatal error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	D3D11_DEPTH_STENCIL_DESC StencilDesc;
	memset(&StencilDesc,0,sizeof(D3D11_DEPTH_STENCIL_DESC));
	StencilDesc.DepthEnable = true;
	StencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	StencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	StencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	StencilDesc.StencilEnable = true;
	StencilDesc.StencilReadMask = 0xFF;
	StencilDesc.StencilWriteMask = 0xFF;
	StencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	StencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	StencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	StencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	ID3D11DepthStencilState* DepthStencilState = nullptr;
	device->CreateDepthStencilState(&StencilDesc, &DepthStencilState);
	context->OMSetDepthStencilState(DepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC StencilViewDesc;
	memset(&StencilViewDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	StencilViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	StencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;

	ID3D11DepthStencilView* DepthStencilView = nullptr;
	r = device->CreateDepthStencilView(StencilTexture, &StencilViewDesc, &DepthStencilView);

	if (DepthStencilView == nullptr)
	{
		MessageBox(nullptr, L"Failed to create ID3D11DepthSentcilView", L"Fatal error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	context->OMSetRenderTargets(1, &MainRenderTarget, DepthStencilView);

	struct LocalVertexDeclaration
	{
		struct p
		{
			float X, Y, Z, W;
		} Pos;
		struct c
		{
			float R, G, B, A;
		} Color;

	} Triangles[3]; 
	Triangles[0] = { {0.0f,  0.5f,  0.0f, 1.0f},{1.0f,0,0,1.0f} }; 
	Triangles[1] = { {0.5f,  -0.5f,  0.0f, 1.0f},{0.0f,1.0f,0,1.0f} }; 
	Triangles[2] = { {-0.5f,  -0.5f,  0.0f, 1.0f},{0.0f,0,1.0f,1.0f} }; 

	D3D11_BUFFER_DESC trianglebufferdesc;
	memset(&trianglebufferdesc, 0, sizeof(D3D11_BUFFER_DESC));
	trianglebufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	trianglebufferdesc.ByteWidth = sizeof(Triangles);
	
	D3D11_SUBRESOURCE_DATA trianglebufferfiller;
	memset(&trianglebufferfiller, 0, sizeof(D3D11_SUBRESOURCE_DATA));
	trianglebufferfiller.pSysMem = Triangles;

	ID3D11Buffer* trianglebuffer = nullptr;
	HRESULT testr = device->CreateBuffer(&trianglebufferdesc, &trianglebufferfiller, &trianglebuffer);
	assert(SUCCEEDED(testr));
	
	ID3DBlob *vs_blob,*vs_e_blob, *ps_blob,*ps_e_blob;

	testr = D3DCompileFromFile(L"VS_NoTransform_PositionColor.hlsl", nullptr, nullptr, "basic_vs", "vs_4_0", 0, 0, &vs_blob, &vs_e_blob);
	testr = D3DCompileFromFile(L"VS_NoTransform_PositionColor.hlsl", nullptr, nullptr, "basic_ps", "ps_4_0", 0, 0, &ps_blob, &ps_e_blob);
	
	assert(SUCCEEDED(testr));
	
	ID3D11PixelShader *_simpleps = nullptr;
	testr = device->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &_simpleps);
	
	assert(SUCCEEDED(testr));

	ID3D11VertexShader* _simplevs = nullptr;
	testr = device->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &_simplevs);

	assert(SUCCEEDED(testr));

	D3D11_SAMPLER_DESC samplerstatedesc;
	memset(&samplerstatedesc, 0, sizeof(samplerstatedesc));
	samplerstatedesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerstatedesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerstatedesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	samplerstatedesc.BorderColor[0] = 1.0f;
	samplerstatedesc.BorderColor[1] = 1.0f;
	samplerstatedesc.BorderColor[2] = 1.0f;
	samplerstatedesc.BorderColor[3] = 1.0f;

	samplerstatedesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerstatedesc.MaxLOD = FLT_MAX;
	samplerstatedesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
	samplerstatedesc.MaxAnisotropy = 1;

	ID3D11SamplerState* samplerstate = nullptr;
	testr = device->CreateSamplerState(&samplerstatedesc, &samplerstate);
	assert(SUCCEEDED(testr));

	context->VSSetSamplers(0, 1, &samplerstate);
	context->PSSetSamplers(0, 1, &samplerstate);

	ID3D11RasterizerState* rasterizerstate = 0;
	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;

	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = true;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	testr = device->CreateRasterizerState(&rasterizerDesc, &rasterizerstate);
	assert(SUCCEEDED(testr));
	context->RSSetState(rasterizerstate);

	D3D11_INPUT_ELEMENT_DESC vs_input_l[] =
	{
		{"POSITION",0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}, // <- this
		{"COLOR",0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,16,D3D11_INPUT_PER_VERTEX_DATA,0} //<- i took D3D11_APPEND_ALIGNED_ELEMENT from some tutorial article
	};

	ID3D11InputLayout* _inputLayout;
	testr = device->CreateInputLayout(vs_input_l, 2, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &_inputLayout);
	assert(SUCCEEDED(testr));

	context->IASetInputLayout(_inputLayout);

	MSG m = { 0 };
	while (true)
	{
		while(PeekMessage(&m,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&m);
			DispatchMessageW(&m);
		}
		float cleancolor[] = {0,0,0,1 };
		context->OMSetRenderTargets(1, &MainRenderTarget, nullptr);
		context->ClearRenderTargetView(MainRenderTarget, cleancolor);

		D3D11_VIEWPORT Viewport;
		memset(&Viewport, 0, sizeof(D3D11_VIEWPORT));
		Viewport.TopLeftX = 0;
		Viewport.TopLeftY = 0;
		Viewport.Width = 800;
		Viewport.Height = 600;
		Viewport.MinDepth = 0.0f;
		Viewport.MaxDepth = 1.0f;

		context->RSSetViewports(1, &Viewport);
		
		context->VSSetShader(_simplevs, nullptr, 0);
		context->PSSetShader(_simpleps, nullptr, 0);
		
		uint32_t vstride = sizeof(LocalVertexDeclaration);
		uint32_t voffset = 0;

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 
		context->IASetVertexBuffers(0, 1, &trianglebuffer, &vstride, &voffset);
		context->Draw(3, 0);

		swapchain->Present(1, 0);
	}
	return EXIT_SUCCESS;
}

LRESULT __stdcall WindowProcessMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			exit(0);
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
					break;
				case MENU_OPENFILE:
					break;
				case MENU_SAVEFILE:
					break;
				case MENU_SAVEFILEAS:
					break;
				case MENU_PLAYPROJECT:
					break;
				case MENU_COMPILEPROJECT:
					break;
				case MENU_EXIT:
				{
					exit(0);
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
				case MENU_INSTALLFILES:
				{
					break;
				}
				case MENU_RESETCURSOR:
				{
					break;
				}
				case MENU_UPDATECHECK:
				{
					CheckAndDownloadUpdate();
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
			exit(0);
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
	SetWindowPos(RenderWindow, nullptr, 0, 0, width, height, SWP_SHOWWINDOW);
}

void CheckAndDownloadUpdate()
{

}
