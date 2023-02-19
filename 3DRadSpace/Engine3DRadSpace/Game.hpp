#pragma once
#include "Window.hpp"
#include "IUpdateable.hpp"
#include "IDrawable.hpp"
#include "IInitializable.hpp"
#include "Point.hpp"

namespace Engine3DRadSpace
{
	class Game : public IUpdateable, public IDrawable, public IInitiializable
	{
		bool valid;
		Math::Point resolution;
	public:
		Game(const char* title, int width = 800, int height = 600, bool fullscreen = false);
		Game(Window&& window);

		Game(Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(Game&) = delete;

		std::unique_ptr<Window> Window;
		std::unique_ptr<GraphicsDevice> Device;

		void Run();

		void RunOneFrame();

		Math::Point Resolution();

		virtual ~Game() = default;
	};
}

