#pragma once
#include "GraphicsDevice.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

namespace Engine3DRadSpace
{
	class Window
	{
		void* window;

		Engine3DRadSpace::Input::Mouse mouse;
		Engine3DRadSpace::Input::Keyboard keyboard;

		void _keyUp(uint8_t k);
		void _keyDown(uint8_t k);
		void _scrollwheel(float dw);
		void _handleMouse(Math::Point pos,bool left,bool middle, bool right);
	public:
		Window(const char* title, int width = 800, int height = 600);
		//Used for the Windows editor frontend.
		Window(void* hInstance, void* parentWindow);
		Window(Window& wnd);

		Window& operator=(Window& wnd) = delete;

		void* NativeHandle();

		/// <summary>
		/// Processes one update-draw cycle.
		/// </summary>
		void ProcessMessages();

		Engine3DRadSpace::Input::Mouse& GetMouseState();
		Engine3DRadSpace::Input::Keyboard& GetKeyboardState();

		Math::Point Size();
		Math::RectangleF RectangleF();
		Math::Rectangle Rectangle();
		bool IsFocused();
		
		void SetMousePosition(const Math::Point& p);

		~Window();

		friend LRESULT CALLBACK GameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

