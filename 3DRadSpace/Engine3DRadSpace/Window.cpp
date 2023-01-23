#include "Window.hpp"

using namespace Engine3DRadSpace;

#ifdef _WIN32
#include <Windows.h>

LRESULT CALLBACK Engine3DRadSpace::GameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* window = nullptr;

    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        window = static_cast<Window*>(cs->lpCreateParams);
        SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    }
    else window = reinterpret_cast<Window*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));

    switch (msg)
    {
        case WM_SYSKEYDOWN:
        case WM_IME_KEYDOWN:
        case WM_KEYDOWN:
        {
            window->_keyDown(static_cast<uint8_t>(wParam));
            break;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP:
        case WM_IME_KEYUP:
        {
            window->_keyUp(static_cast<uint8_t>(wParam));
            break;
        }
        case WM_MOUSEWHEEL:
        {
            window->_scrollwheel(HIWORD(wParam));
            break;
        }
        default: break;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

#endif

void Engine3DRadSpace::Window::_keyUp(uint8_t k)
{
    switch (k)
    {
        case VK_LBUTTON:
            _mouse._leftButton = true;
            break;
        case VK_RBUTTON:
            _mouse._rightButton = true;
            break;
        case VK_MBUTTON:
            _mouse._middleButton = true;
        default:
            _keyboard._removeKey(k);
            break;
    }
}

void Engine3DRadSpace::Window::_keyDown(uint8_t k)
{
    switch (k)
    {
        case VK_LBUTTON:
            _mouse._leftButton = false;
            break;
        case VK_RBUTTON:
            _mouse._rightButton = false;
            break;
        case VK_MBUTTON:
            _mouse._middleButton = false;
        default:
            _keyboard._addKey(k);
            break;
    }
}

void Engine3DRadSpace::Window::_scrollwheel(float dw)
{
    _mouse._scrollWheel += dw / WHEEL_DELTA;
}

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
    if (a == 0) throw std::runtime_error("Failed to register the window class for the game window!");

    _window = CreateWindowExA(
        0,
        "3DRSP_GAME",
        "",
        WS_VISIBLE | WS_CHILD,
        0,
        0,
        800,
        600,
        static_cast<HWND>(parentWindow),
        nullptr,
        static_cast<HINSTANCE>(hInstance),
        this
    );
    if (_window == nullptr) throw std::runtime_error("Failed to create a Windows window instance!");
#endif
}

void* Engine3DRadSpace::Window::NativeHandle()
{
    return _window;
}

void Engine3DRadSpace::Window::ProcessMessages()
{
#ifdef _WIN32
    MSG msg;
    if(PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    POINT cursorPos;
    BOOL b = GetCursorPos(&cursorPos);
    if (b > 0)
    {
        this->_mouse._position = Math::Point(cursorPos.x, cursorPos.y);
    }
#endif
}

Engine3DRadSpace::Input::Mouse& Engine3DRadSpace::Window::GetMouseState()
{
    return _mouse;
}

Engine3DRadSpace::Input::Keyboard& Engine3DRadSpace::Window::GetKeyboardState()
{
    return _keyboard;
}

Math::Point Engine3DRadSpace::Window::Size()
{
    RECT r;
    GetWindowRect(static_cast<HWND>(_window), &r);

    return { r.right - r.left, r.bottom - r.top };
}

Engine3DRadSpace::Window::~Window()
{

}