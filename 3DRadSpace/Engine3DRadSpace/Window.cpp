#include "Window.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Input;

#ifdef _WIN32
#include <Windows.h>
#include <windowsx.h>

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
        case WM_MOUSEACTIVATE:
        {
            HWND renderWindow = static_cast<HWND>(window->_window);
            SetForegroundWindow(renderWindow);
            SetFocus(renderWindow);
            break;
        }
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        {
            window->_keyDown(static_cast<uint8_t>(wParam));
            return 0;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            window->_keyUp(static_cast<uint8_t>(wParam));
            return 0;
        }
        case WM_KILLFOCUS:
        {
            window->_resetKeyboard();
            return 0;
        }
        case WM_MOUSEWHEEL:
        {
            window->_scrollwheel(GET_WHEEL_DELTA_WPARAM(wParam));
            break;
        }
        case WM_MOUSEMOVE:
        {
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);

            bool lBtn = (bool)(wParam & MK_LBUTTON);
            bool mBtn = (bool)(wParam & MK_MBUTTON);
            bool rBtn = (bool)(wParam & MK_RBUTTON);

            window->_handleMouse({ x,y }, lBtn, mBtn, rBtn);
            break;
        }
        case WM_CLOSE:
        {
            window->_window = nullptr;
            break;
        }
        default: break;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

#endif

void Window::_keyUp(uint8_t k)
{
    switch (k)
    {
        case VK_LBUTTON:
            _mouse._leftButton = ButtonState::Pressed;
            break;
        case VK_RBUTTON:
            _mouse._rightButton = ButtonState::Pressed;
            break;
        case VK_MBUTTON:
            _mouse._middleButton = ButtonState::Pressed;
            break;
        default:
            _keyboard._removeKey(k);
            break;
    }
}

void Window::_keyDown(uint8_t k)
{
    switch (k)
    {
        case VK_LBUTTON:
            _mouse._leftButton = ButtonState::Released;
            break;
        case VK_RBUTTON:
            _mouse._rightButton = ButtonState::Released;
            break;
        case VK_MBUTTON:
            _mouse._middleButton = ButtonState::Released;
            break;
        default:
            _keyboard._addKey(k);
            break;
    }
}

void Window::_scrollwheel(float dw)
{
    _mouse._scrollWheel += dw / WHEEL_DELTA;
}

void Window::_handleMouse(Point pos, bool left, bool middle, bool right)
{
    auto rectangle = this->Rectangle();

    _mouse._position = pos - Point(rectangle.X, rectangle.Y); //substract top-left point to make mouse coordinates screen relative.
    _mouse._leftButton = static_cast<ButtonState>(left);
    _mouse._middleButton = static_cast<ButtonState>(middle);
    _mouse._rightButton = static_cast<ButtonState>(right);
}

void Window::_resetKeyboard()
{
    _keyboard._erase();
}

Window::Window(const char* title, int width, int height)
{
#ifdef _WIN32
    WNDCLASSA wndclass{};
    wndclass.lpszClassName = "3DRSP_GAME";
    wndclass.lpfnWndProc = GameWndProc;
    wndclass.hInstance = GetModuleHandleA(nullptr); //In x86 and x64, HMODULE = HINSTANCE
    //wndclass.hIcon = LoadIconA(wndclass.hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wndclass.hCursor = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512)); //IDI_CURSOR
    
    ATOM a = RegisterClassA(&wndclass);
    if (a == 0) throw std::runtime_error("Failed to register the window class for the game window!");

    _hInstance = wndclass.hInstance;

    _window = CreateWindowExA(
        0, 
        "3DRSP_GAME",
        title, 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        nullptr, 
        nullptr,
        wndclass.hInstance, 
        this
    );
#endif
}

Window::Window(void* hInstance,void* parentWindow)
{
#ifdef _WIN32
    WNDCLASSA wndclass{};
    wndclass.lpszClassName = "3DRSP_GAME";
    wndclass.lpfnWndProc = GameWndProc;
    wndclass.hInstance = static_cast<HINSTANCE>(hInstance);
    
    ATOM a = RegisterClassA(&wndclass);
    //if (a == 0) throw std::runtime_error("Failed to register the window class for the game window!");

    _hInstance = wndclass.hInstance;

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

    ShowWindow(static_cast<HWND>(_window),SW_NORMAL);
    SetForegroundWindow(static_cast<HWND>(_window));
    SetFocus(static_cast<HWND>(_window));
#endif
}

Window::Window(Window &&wnd) noexcept:
    _window(wnd._window)
#ifdef _WIN32
	,_hInstance(wnd._hInstance)
#endif
{
    wnd._window = nullptr;
#ifdef _WIN32
    wnd._hInstance = nullptr;
    SetWindowLongPtrA(static_cast<HWND>(this->_window), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
#endif // 
}

Window& Window::operator=(Window &&wnd) noexcept
{
    _window = wnd._window;
    wnd._window = nullptr;

#ifdef _WIN32
    SetWindowLongPtrA(static_cast<HWND>(this->_window), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
#endif // 
    return *this;
}

void* Window::NativeHandle()
{
    return this->_window;
}

void Window::ProcessMessages()
{
#ifdef _WIN32
    MSG msg;
    while(PeekMessageA(&msg, nullptr, 0, 0,PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
#endif
}

Input::Mouse& Window::GetMouseState()
{
    return _mouse;
}

Input::Keyboard& Window::GetKeyboardState()
{
    return _keyboard;
}

Point Window::Size()
{
    RECT r;
    GetWindowRect(static_cast<HWND>(_window), &r);

    return { r.right - r.left, r.bottom - r.top };
}

RectangleF Window::RectangleF()
{
#ifdef  _WIN32
    RECT r;
    GetClientRect(static_cast<HWND>(_window), &r);
    
    return { (float)r.left, (float)r.top, (float)(r.right - r.left), (float)(r.bottom - r.top) };
#endif //  _WIN32
}

Math::Rectangle Window::Rectangle()
{
#ifdef  _WIN32
    RECT r;
    GetClientRect(static_cast<HWND>(_window), &r);

    return {r.left, r.top, r.right - r.left, r.bottom - r.top };
#endif //  _WIN32
}

bool Window::IsFocused()
{
    return GetForegroundWindow() == _window;
}

void Window::SetMousePosition(const Point& p)
{
#ifdef _WIN32
    POINT mp = { p.X, p.Y };
    MapWindowPoints(static_cast<HWND>(_window), nullptr, &mp, 1);

    _mouse._position = { mp.x, mp.y };
    BOOL r = SetCursorPos(_mouse._position.X, _mouse._position.Y);
    if (!r)
    {
        throw std::system_error(
            std::error_code(GetLastError(), std::system_category()),
            "Failed to set the mouse position!"
        );
    }
#endif
}

Window::~Window()
{
#ifdef _WIN32
    DestroyWindow(static_cast<HWND>(_window));
    UnregisterClassA("3DRSP_GAME", _hInstance);
#endif
}