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

namespace Engine3DRadSpace
{
	class Game : public IUpdateable, public IDrawable3D, public IDrawable2D, public IInitiializable, public ILoadable
	{
		bool _valid;
		bool _running = true;

		double u_dt = 0;
		double d_dt = 0;

		/// Valid unsigned values :
		/// 1u = IObject
		/// 2u = IObject2D
		/// 3u = IObject3D
		std::vector<std::pair<unsigned, std::unique_ptr<IObject>>> objects;
		unsigned lastId = 1;

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

		std::unique_ptr<Engine3DRadSpace::Content::ContentManager> Content;

		void Run();
		void RunOneFrame();
		void Exit();

		void AddObject(IObject *obj);
		void AddObject(IObject2D *obj);
		void AddObject(IObject3D *obj);

		IObject *FindObject(unsigned id);
		IObject *FindObject(const std::string &name);

		void RemoveObject(unsigned id);
		void RemoveObjects(const std::string &name);
		void RemoveObjects(IObject *obj);

		void RemoveObjectsIf(std::function<bool(IObject*)> f);

		virtual ~Game() = default;

		virtual void Initialize() override;
		virtual void Load(Content::ContentManager *content) override;
		virtual void Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt) override;
		virtual void Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt) override;
		virtual void Draw(Graphics::SpriteBatch *spriteBatch, double dt) override;
	};
}

