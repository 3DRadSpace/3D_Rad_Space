#define NOMINMAX
#include <cstdlib>
#include "Engine3DRadSpace/Error.hpp"
#include "EditorWindow.hpp"

#include <PathCch.h>
#pragma comment(lib,"Comctl32.lib")

#include <commctrl.h>
#pragma comment(lib,"Pathcch.lib")

#include "HelperFunctions.hpp"

//Enable visual styles
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace Engine3DRadSpace::Logging;

void HandleError()
{
	if (LastError.ErrorCode < 0)
	{
		MessageBoxA(nullptr, LastError.Details, "Fatal error!", MB_ICONERROR | MB_OK);
	}
}

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
	// Load controls such as the progress bar, tree views, list views, et cetera...
	INITCOMMONCONTROLSEX iccs{};
	iccs.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccs.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&iccs);
}

int __stdcall WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR cmdArgs,_In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance); //hPrevInstance was only used in 16-bit Windows applications.
	UNREFERENCED_PARAMETER(nShowCmd); //The editor windows is maximized anyways.
	std::atexit(HandleError);

	InitializeGDI();
	InitializeCommonControls();
	SetWorkingDirectory();

	EditorWindow editor(hInstance, cmdArgs);
	editor.Run();

	DeinitializeGDI();
	return 0;
}