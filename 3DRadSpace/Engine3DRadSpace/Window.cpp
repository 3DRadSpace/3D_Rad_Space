#include "Window.hpp"

#ifdef _WIN32
#include <Windows.h>

LRESULT GameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        default: break;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

#endif

Engine3DRadSpace::Window::Window(const char* title, int width, int height)
{
    //Create a Windows window
#ifdef _WIN32
    WNDCLASSA wndclass{};
    wndclass.lpszClassName = "3DRSP_GAME";
    wndclass.lpfnWndProc = GameWndProc;
    wndclass.hInstance = nullptr;
#endif
}

Engine3DRadSpace::Window::Window(void* hInstance,void* parentWindow)
{
#ifdef _WIN32
    WNDCLASSA wndclass{};
    wndclass.lpszClassName = "3DRSP_GAME";
    wndclass.lpfnWndProc = GameWndProc;
    wndclass.hInstance = static_cast<HINSTANCE>(hInstance);
    
    ATOM a = RegisterClassA(&wndclass);

    _window = CreateWindowExA(
        0,
        "3DRSP_GAME",
        "",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0,
        0,
        800,
        600,
        static_cast<HWND>(parentWindow),
        nullptr,
        static_cast<HINSTANCE>(hInstance),
        nullptr
    );
    if (_window == nullptr) throw std::runtime_error("Failed to create a Windows window instance!");
#endif
}

void* Engine3DRadSpace::Window::NativeHandle()
{
    return _window;
}

void Engine3DRadSpace::Window::ProcessFrame()
{
    MSG msg;
    if(PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

void Engine3DRadSpace::Window::Run()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

Engine3DRadSpace::Window::~Window()
{

}
