#pragma once
#include "GraphicsDevice.hpp"

namespace Engine3DRadSpace
{
	class Window
	{
		void* _window;
	public:
		Window(const char* title, int width = 800, int height = 600);
		//Used for the Windows frontend.
		Window(void* hInstance, void* parentWindow);
		void* NativeHandle();

		/// <summary>
		/// Processes one update-draw cycle.
		/// </summary>
		void ProcessFrame();

		/// <summary>
		/// Processes update-draw cycles until the window is destroyed.
		/// </summary>
		void Run();



		~Window();
	};
}

