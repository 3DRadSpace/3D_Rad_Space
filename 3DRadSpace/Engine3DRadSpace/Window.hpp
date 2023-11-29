#pragma once
#include "GraphicsDevice.hpp"
#include "Input/Mouse.hpp"
#include "Input/Keyboard.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT Window
	{
		void* _window;

#ifdef _WIN32
		HINSTANCE _hInstance;
#endif

		Input::Mouse _mouse;
		Input::Keyboard _keyboard;

		void _keyUp(uint8_t k);
		void _keyDown(uint8_t k);
		void _scrollwheel(float dw);
		void _handleMouse(Math::Point pos,bool left,bool middle, bool right);
		void _resetKeyboard();
	public:
		Window(const std::string& title, int width = 800, int height = 600);
		//Used for the Windows editor frontend.
		Window(void* hInstance, void* parentWindow);

		Window(Window &) = delete;
		Window(Window &&wnd) noexcept;

		Window& operator=(Window& wnd) = delete;
		Window &operator=(Window &&wnd) noexcept;

		void* NativeHandle();

		/// <summary>
		/// Processes one update-draw cycle.
		/// </summary>
		void ProcessMessages();

		Input::Mouse& GetMouseState();
		Input::Keyboard& GetKeyboardState();

		Math::Point Size();
		Math::RectangleF RectangleF();
		Math::Rectangle Rectangle();
		bool IsFocused();
		
		void SetMousePosition(const Math::Point& p);

		~Window();

		friend LRESULT DLLEXPORT CALLBACK GameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

