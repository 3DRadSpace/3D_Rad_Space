#pragma once
#include "Window.hpp"
#include "IUpdateable.hpp"
#include "IDrawable.hpp"
#include "IInitializable.hpp"
#include "IObject.hpp"
#include "Math/Matrix.hpp"

namespace Engine3DRadSpace
{
	class Game : public IUpdateable, public IDrawable, public IInitiializable
	{
		bool _valid;
		bool _running = true;

		double u_dt = 0;
		double d_dt = 0;
	public:
		Game(const char* title, int width = 800, int height = 600, bool fullscreen = false);
		Game(Window&& window);

		Game(Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(Game&) = delete;

		std::unique_ptr<Window> Window;
		std::unique_ptr<GraphicsDevice> Device;

		Engine3DRadSpace::Math::Matrix View;
		Engine3DRadSpace::Math::Matrix Projection;

		std::vector<std::unique_ptr<Engine3DRadSpace::IObject>> Objects;

		void Run();

		void RunOneFrame();

		void Exit();

		virtual ~Game() = default;
	};
}

