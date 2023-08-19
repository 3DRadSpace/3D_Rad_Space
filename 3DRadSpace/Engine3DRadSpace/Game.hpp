#pragma once
#include "Window.hpp"
#include "IUpdateable.hpp"
#include "IDrawable3D.hpp"
#include "IDrawable2d.hpp"
#include "IInitializable.hpp"
#include "IObject2D.hpp"
#include "IObject3D.hpp"
#include "ILoadable.hpp"
#include "Math/Matrix.hpp"
#include "Content/ContentManager.hpp"
#include "Graphics/SpriteBatch.hpp"
#include "Reflection/ReflectedObject.hpp"
#include "ObjectList.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT Game : public IUpdateable, public IDrawable3D, public IDrawable2D, public IInitiializable, public ILoadable
	{
	private:
		bool _valid;
		bool _running = true;

		double u_dt = 0;
		double d_dt = 0;
	public:
		Game(const char* title, unsigned width = 800, unsigned height = 600, bool fullscreen = false);
		Game(Window&& window);

		Game(Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(Game&) = delete;

		std::unique_ptr<Window> Window;
		std::unique_ptr<GraphicsDevice> Device;
		ObjectList Objects;

		Engine3DRadSpace::Math::Matrix View;
		Engine3DRadSpace::Math::Matrix Projection;

		std::unique_ptr<Engine3DRadSpace::Content::ContentManager> Content;

		std::unique_ptr<Engine3DRadSpace::Graphics::SpriteBatch> SpriteBatch;

		Color ClearColor = Colors::Black;

		void Run();
		void RunOneFrame();
		void Exit();

		virtual ~Game() = default;

		virtual void Initialize() override;
		virtual void Load(Content::ContentManager* content) override;
		virtual void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override;
		virtual void Draw(Engine3DRadSpace::Math::Matrix& view, Engine3DRadSpace::Math::Matrix& projection, double dt) override;
		virtual void Draw(Graphics::SpriteBatch* spriteBatch, double dt) override;
	};
}
