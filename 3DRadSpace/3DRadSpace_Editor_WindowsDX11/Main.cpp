#define NOMINMAX
#include <cstdlib>
#include "Frontend\Windows\EditorWindow.hpp"
#include "Frontend\HelperFunctions.hpp"

#include <PathCch.h>
#pragma comment(lib,"Comctl32.lib")

#include <commctrl.h>
#pragma comment(lib,"Pathcch.lib")

//Enable visual styles
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <dxgi1_3.h>
#include <DXGIDebug.h>
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "dxguid.lib")

#include <Engine3DRadSpace/Content/ShaderManager.hpp>
#include "Engine3DRadSpace/Logging/Exception.hpp"
#include "Frontend/Settings.hpp"
#include "Editor/SkinmeshPreviewer.hpp"

using namespace Engine3DRadSpace::Logging;

void SetWorkingDirectory()
{
	//Sets working directory to the executable's folder.
	wchar_t currentDir[_MAX_PATH]{};
	GetModuleFileNameW(nullptr, currentDir, _MAX_PATH);
	PathCchRemoveFileSpec(currentDir, _MAX_PATH);

	SetCurrentDirectoryW(currentDir);
}

void InitializeCommonControls()
{
	// Load controls such as the progress bar, tree views, list views, etc...
	INITCOMMONCONTROLSEX iccs{};
	iccs.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccs.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&iccs);
}

#ifdef _DEBUG
void ReportLiveObjects()
{
	Microsoft::WRL::ComPtr<IDXGIDebug1> dxgi_debug;
	if(SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgi_debug.GetAddressOf()))))
	{
		dxgi_debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
	}
}
#endif

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR cmdArgs, _In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance); //hPrevInstance was only used in 16-bit Windows applications.
	UNREFERENCED_PARAMETER(nShowCmd); //The editor windows is maximized anyways.

#ifdef _DEBUG
	std::atexit(ReportLiveObjects); // Lists leaked DX11 objects
#endif

	InitializeGDI();
	InitializeCommonControls();
	SetWorkingDirectory();

	if (FAILED(CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED)))
		return -1;

	Settings::Load();

	EditorWindow editor(hInstance, cmdArgs);
	editor.Run();

	DeinitializeGDI();
	CoUninitialize();

	//Manually release the stored shaders inside the ShaderManager class. 
	//This is necessary to avoid reports of live objects when the debug layer detects the application process being terminated, even if the destructors are called when the program terminates.
	Engine3DRadSpace::Content::ShaderManager::ReleaseAll();

	return 0;
}