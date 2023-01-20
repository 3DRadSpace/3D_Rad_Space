#pragma once
#include "Window.hpp"
#include "IUpdateable.hpp"
#include "IDrawable.hpp"

namespace Engine3DRadSpace
{
	class Game : public IUpdateable, public IDrawable
	{
		std::unique_ptr<Window> window;
		std::unique_ptr<GraphicsDevice> device;
	public:
		Game(const char* title, int width = 800, int height = 600, bool fullscreen = false);

		void Run();
	};
}

