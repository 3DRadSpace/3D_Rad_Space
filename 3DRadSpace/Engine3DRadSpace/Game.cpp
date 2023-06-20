#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;

Game::Game(const char* title, int width, int height, bool fullscreen) :
	Window(std::make_unique<Engine3DRadSpace::Window>(title, width, height))
{
	Device = std::make_unique<Engine3DRadSpace::GraphicsDevice>(Window->NativeHandle(),width,height);
	Content = std::make_unique<Engine3DRadSpace::Content::ContentManager>(Device.get());
	_valid = true;
}

Engine3DRadSpace::Game::Game(Engine3DRadSpace::Window &&window) :
	Window(std::make_unique<Engine3DRadSpace::Window>(std::move(window)))
{
	Math::Point size = Window->Size();

	Device = std::make_unique<GraphicsDevice>(Window->NativeHandle(), size.X, size.Y);
	Content = std::make_unique<Engine3DRadSpace::Content::ContentManager>(Device.get());
	_valid = true;
}

void Game::Run()
{
	Initialize();
	Load(Content.get());
	while (_running)
	{	
		RunOneFrame();
	}
}

void Engine3DRadSpace::Game::RunOneFrame()
{
	Window->ProcessMessages();

	auto ts_u1 = std::chrono::high_resolution_clock::now();
	this->Update(Window->GetKeyboardState(), Window->GetMouseState(), u_dt);
	auto ts_u2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
	u_dt = uDiff.count();

	auto ts_d1 = std::chrono::high_resolution_clock::now();

	this->Device->SetViewport(Viewport(this->Window->RectangleF(), 0.0f, 1.0f));
	this->Device->Clear();
	this->Draw(View,Projection,d_dt);

	this->Device->Present();

	auto ts_d2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> dDiff = ts_d2 - ts_d1;
	d_dt = dDiff.count();
}

void Engine3DRadSpace::Game::Exit()
{
	_running = false;
}

void Engine3DRadSpace::Game::AddObject(IObject *obj)
{
	std::unique_ptr<IObject> ptr;
	ptr.reset(obj);

	objects[lastId++] = std::make_pair(1u, std::move(ptr));
}

void Engine3DRadSpace::Game::AddObject(IObject2D *obj)
{
	std::unique_ptr<IObject2D> ptr;
	ptr.reset(obj);

	objects[lastId++] = std::make_pair(2u, std::move(ptr));
}

void Engine3DRadSpace::Game::AddObject(IObject3D *obj)
{
	std::unique_ptr<IObject3D> ptr;
	ptr.reset(obj);

	objects[lastId++] = std::make_pair(3u, std::move(ptr));
}

IObject *Engine3DRadSpace::Game::FindObject(unsigned id)
{
	for(auto &pair : objects)
	{
		if(pair.first == id)
			return pair.second.get();
	}
	return nullptr;
}

IObject *Engine3DRadSpace::Game::FindObject(const std::string &name)
{
	for(auto &pair : objects)
	{
		if(pair.second->Name == name)
			return pair.second.get();
	}
	return nullptr;
}

void Engine3DRadSpace::Game::RemoveObject(unsigned id)
{
	objects.erase(objects.begin() + id, objects.begin() + id + 1);
}

void Engine3DRadSpace::Game::RemoveObjects(const std::string &name)
{
	std::erase_if(objects, [name](std::pair<unsigned, std::unique_ptr<IObject>> &p) -> bool
	{
		return p.second->Name == name;
	});
}

void Engine3DRadSpace::Game::RemoveObjects(IObject *obj)
{
	std::erase_if(objects, [obj](std::pair<unsigned, std::unique_ptr<IObject>> &p) -> bool
	{
		return p.second.get() == obj;
	});
}

void Engine3DRadSpace::Game::RemoveObjectsIf(std::function<bool(IObject*)> f)
{
	std::erase_if(objects, [f](std::pair<unsigned, std::unique_ptr<IObject>> &p) -> bool
	{
		return f(p.second.get());
	});
}

void Engine3DRadSpace::Game::Load(Content::ContentManager *content)
{
	for(auto &p : objects)
	{
		p.second->Load(content);
	}
}

void Engine3DRadSpace::Game::Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt)
{
	for(auto &p : objects)
	{
		p.second->Update(keyboard, mouse, dt);
	}
}

void Engine3DRadSpace::Game::Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt)
{
	for(auto &p : objects)
	{
		if(p.first == 3u)
		{
			(static_cast<IObject3D *>(p.second.get()))->Draw(view, projection, dt);
		}
	}
}

void Engine3DRadSpace::Game::Draw(Graphics::SpriteBatch *spriteBatch, double dt)
{
	for(auto &p : objects)
	{
		if(p.first == 2u)
		{
			(static_cast<IObject2D *>(p.second.get()))->Draw(spriteBatch, dt);
		}
	}
}

void Engine3DRadSpace::Game::Initialize()
{
	for(auto &p : objects)
	{
		p.second->Initialize();
	}
}
