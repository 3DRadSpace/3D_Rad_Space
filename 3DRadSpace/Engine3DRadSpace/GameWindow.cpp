#include "GameWindow.hpp"
#ifdef _WIN32
#include <Windows.h>	
#endif // _WIN32

Engine3DRadSpace::GameWindow::GameWindow(const char* title, unsigned width, unsigned height)
{
#ifdef _WIN32
	WNDCLASSA wndclass{};
	wndclass.lpszClassName = "3DRSP_GAME";
#endif // _WIN32

}