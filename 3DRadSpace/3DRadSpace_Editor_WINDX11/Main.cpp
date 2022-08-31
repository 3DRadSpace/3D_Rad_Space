#include "MainWindow.hpp"
#include <iostream>


/// <summary>
/// The entry function to the game engine editor.
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance">Windows specific unused argument.</param>
/// <param name="args">command line arguments (ex project file)</param>
/// <param name="nShowCmd">Not used. The main window is directly maximized.</param>
/// <returns></returns>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_  PWSTR args, _In_  int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

#if _DEBUG
	AllocConsole();
	FILE* new_stdout = nullptr;
	freopen_s(&new_stdout, "CONOUT$", "w", stdout);
#endif

	InitializeGDI();
	std::cout << "Initialized GDI \r\n";

	EditorWindow Editor(hInstance, args);
	Editor.RenderUpdateLoop();
	DeinitializeGDI();

#if _DEBUG
	FreeConsole();
#endif
	return 0;
}