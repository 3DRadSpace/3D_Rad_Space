#define NOMINMAX
#include <cstdlib>
#include "Engine3DRadSpace/Error.hpp"
#include "EditorWindow.hpp"

#include <commctrl.h>
#pragma comment(lib,"Comctl32.lib")

using namespace Engine3DRadSpace::Logging;

void HandleError()
{
	if (LastError.ErrorCode < 0)
	{
		MessageBoxA(nullptr, LastError.Details, "Fatal error!", MB_ICONERROR | MB_OK);
	}
}

int __stdcall WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR cmdArgs,_In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance); //hPrevInstance was only used in 16-bit Windows applications.
	UNREFERENCED_PARAMETER(nShowCmd); //The editor windows is maximized anyways.
	std::atexit(HandleError);

	
	INITCOMMONCONTROLSEX iccs{};
	iccs.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccs.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&iccs);

	EditorWindow editor(hInstance, cmdArgs);
	editor.Update();

	return 1;
}