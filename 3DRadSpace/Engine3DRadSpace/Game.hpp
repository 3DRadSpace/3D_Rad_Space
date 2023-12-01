#pragma once
#include "Window.hpp"
#include "IUpdateable.hpp"
#include "IDrawable3D.hpp"
#include "IDrawable2d.hpp"
#include "IInitializable.hpp"
#include "IObject2D.hpp"
#include "IObject3D.hpp"
#include "ILoadable.hpp"
#include "Math\Matrix4x4.hpp"
#include "Content/ContentManager.hpp"
#include "Graphics/SpriteBatch.hpp"
#include "Reflection/ReflectedObject.hpp"
#include "ObjectList.hpp"
#include "Physics/PhysicsEngine.hpp"

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
		Game(const std::string &title, unsigned width = 800, unsigned height = 600, bool fullscreen = false);
		Game(Window&& window);

		Game(Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;

		std::unique_ptr<Window> Window;
		std::unique_ptr<GraphicsDevice> Device;
		ObjectList Objects;

		Math::Matrix4x4 View;
		Math::Matrix4x4 Projection;

		std::unique_ptr<Content::ContentManager> Content;

		std::unique_ptr<Graphics::SpriteBatch> SpriteBatch;

		Color ClearColor = Colors::Black;

		std::unique_ptr<Physics::PhysicsEngine> Physics;

		void Run();
		void RunOneFrame();
		void Exit();

		void RequestPhysicsInitialization(const Math::Vector3& gravity, double timeStep = 1.0 / 60.0);
		Math::Ray GetMouseRay(const Math::Vector2& mousePosition, const Math::Matrix4x4& view, const Math::Matrix4x4& projection);

		virtual ~Game();

		virtual void Initialize() override;
		virtual void Load(Content::ContentManager* content) override;
		virtual void Load(Content::ContentManager* content, const std::filesystem::path &path) override;
		virtual void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override;
		virtual void Draw(Math::Matrix4x4& view, Math::Matrix4x4& projection, double dt) override;
		virtual void Draw(Graphics::SpriteBatch* spriteBatch, double dt) override;
	};
}
