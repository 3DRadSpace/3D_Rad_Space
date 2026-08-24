#pragma once
#include "../Graphics/IGraphicsDevice.hpp"
#include "../Input/Mouse.hpp"
#include "../Input/Keyboard.hpp"

namespace Engine3DRadSpace::Native
{
	/// <summary>
	/// Represents an application window and provides access to input devices.
	/// </summary>
	class E3DRSP_NATIVE_EXPORT Window
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
		void _handleMouse(bool* left, bool* middle, bool* right);
		void _resetKeyboard();
	public:
		/// <summary>
		///	Constructs an Window with the specified title and size.
		/// </summary>
		/// <param name="title">Title of the window</param>
		/// <param name="width">Width of the window and backbuffer</param>
		/// <param name="height">Height of the window and backbuffer</param>
		Window(const std::string& title, size_t width = 800, size_t height = 600);
		/// <summary>
		/// Constructs an window from the specified window handles.
		/// </summary>
		/// <param name="hInstance">Windows: HINSTANCE, Linux: unused, TODO</param>
		/// <param name="parentWindow">Windows: HWND, Linux: GLFWwindow*, TODO</param>
		/// <remarks>
		/// Used for the Windows editor frontend.
		/// </remarks>
		Window(void* hInstance, void* parentWindow);

		Window(Window &) = delete;
		/// <summary>
		/// Move constructor. Transfers ownership of the window to this instance.
		/// </summary>
		/// <param name="wnd">The window to move.</param>
		Window(Window &&wnd) noexcept;

		Window& operator=(Window& wnd) = delete;
		/// <summary>
		/// Move assigment operator. Transfers ownership of the window to this instance.
		/// </summary>
		/// <param name="wnd">The window to move.</param>
		/// <returns>The window instance with transferred ownership.</returns>
		Window &operator=(Window &&wnd) noexcept;

		/// <summary>
		/// Returns the HWND of this window.
		/// </summary>
		/// <returns>The native handle of the window.</returns>
		void* NativeHandle() const noexcept;

		/// <summary>
		/// Processes all pending window messages.
		/// </summary>
		void ProcessMessages();

		/// <summary>
		/// Gets the last recorded mouse state of this window.
		/// </summary>
		/// <returns>The last recorded mouse state.</returns>
		Input::Mouse& GetMouseState();
		/// <summary>
		/// Gets the last recorded keyboard state of this window.
		/// </summary>
		/// <returns>The last recorded keyboard state.</returns>
		Input::Keyboard& GetKeyboardState();

		/// <summary>
		/// Retrieves the size of this Window.
		/// </summary>
		/// <returns>The size of the window.</returns>
		Math::Point Size() const noexcept;
		/// <summary>
		/// Returns the rectangle (PosX, PosY, Width, Height) of this Window.
		/// </summary>
		/// <returns>The rectangle of the window.</returns>
		Math::RectangleF RectangleF() const noexcept;
		/// <summary>
		/// Returns the rectangle (PosX, PosY, Width, Height) of this Window.
		/// </summary>
		/// <returns>The rectangle of the window.</returns>
		Math::Rectangle Rectangle() const noexcept;
		/// <summary>
		/// Is this window currently focused?
		/// </summary>
		/// <returns>Whether the window is currently focused</returns>
		bool IsFocused() const noexcept;
		
		/// <summary>
		/// Sets the mouse position in desktop space coordinates. The position is relative to the top-left corner of the primary monitor.
		/// </summary>
		/// <param name="p">The position to set the mouse to.</param>
		void SetMousePosition(const Math::Point& p);

		/// <summary>
		/// Sets the window title.
		/// </summary>
		/// <param name="title">Title string.</param>
		void SetTitle(const std::string& title);

		/// <summary>
		/// Is the mouse visible?
		/// </summary>
		/// <returns>True if the mouse is visible</returns>
		bool IsMouseVisible();
		/// <summary>
		///	Sets the mouse visibility.
		/// </summary>
		/// <param name="visible">Whether the mouse should be visible</param>
		void SetMouseVisibility(bool visible);

		~Window();

#ifdef _WIN32
		friend LRESULT E3DRSP_NATIVE_EXPORT CALLBACK GameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
	};
}

