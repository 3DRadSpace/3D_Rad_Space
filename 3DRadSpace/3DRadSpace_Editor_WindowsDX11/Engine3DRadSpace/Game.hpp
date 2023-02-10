#pragma once
#include "Window.hpp"
#include "IUpdateable.hpp"
#include "IDrawable.hpp"

namespace Engine3DRadSpace
{
	class Game : public IUpdateable, public IDrawable
	{
		bool _valid;
	public:
		Game(const char* title, int width = 800, int height = 600, bool fullscreen = false);
		Game(Window* window);

		std::unique_ptr<Window> Window;
		std::unique_ptr<GraphicsDevice> Device;

		void Run();

		void RunOneFrame();

		virtual ~Game() = default;
	};
}

