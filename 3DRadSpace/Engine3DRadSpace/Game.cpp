#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Graphics;

Game::Game(const char* title, unsigned width, unsigned height, bool fullscreen) :
	Window(std::make_unique<Engine3DRadSpace::Window>(title, width, height))
{
	Device = std::make_unique<Engine3DRadSpace::GraphicsDevice>(Window->NativeHandle(),width,height);
	Content = std::make_unique<Engine3DRadSpace::Content::ContentManager>(Device.get());
	SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
	_valid = true;
}

Engine3DRadSpace::Game::Game(Engine3DRadSpace::Window &&window) :
	Window(std::make_unique<Engine3DRadSpace::Window>(std::move(window)))
{
	Math::Point size = Window->Size();

	Device = std::make_unique<GraphicsDevice>(Window->NativeHandle(), size.X, size.Y);
	Content = std::make_unique<Content::ContentManager>(Device.get());
	SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
	_valid = true;
}

void Game::Run()
{
	Initialize();
	Load(Content.get());
	while (_running && Window->NativeHandle() != nullptr)
	{	
		Window->ProcessMessages();
		RunOneFrame();
	}
}

void Engine3DRadSpace::Game::RunOneFrame()
{
	auto ts_u1 = std::chrono::high_resolution_clock::now();
	this->Update(Window->GetKeyboardState(), Window->GetMouseState(), u_dt);
	auto ts_u2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
	u_dt = uDiff.count();

	auto ts_d1 = std::chrono::high_resolution_clock::now();

	this->Device->SetViewport();
	this->Device->Clear(ClearColor);
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

unsigned Engine3DRadSpace::Game::AddObject(IObject *obj)
{
	std::unique_ptr<IObject> ptr;
	ptr.reset(obj);

	objects.push_back(std::make_pair(1u, std::move(ptr)));
	return unsigned(objects.size() - 1);
}

unsigned Engine3DRadSpace::Game::AddObject(IObject2D *obj)
{
	std::unique_ptr<IObject2D> ptr;
	ptr.reset(obj);

	objects.push_back(std::make_pair(2u, std::move(ptr)));
	return unsigned(objects.size() - 1);
}

unsigned Engine3DRadSpace::Game::AddObject(IObject3D *obj)
{
	std::unique_ptr<IObject3D> ptr;
	ptr.reset(obj);

	objects.push_back(std::make_pair(3u, std::move(ptr)));
	return unsigned(objects.size() - 1);
}

IObject *Engine3DRadSpace::Game::FindObject(unsigned id)
{
	return objects[id].second.get();
}

IObject *Engine3DRadSpace::Game::FindObject(const std::string &name)
{
	for(auto &[id, object] :objects)
	{
		if(object->Name == name)
			return object.get();
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

void Engine3DRadSpace::Game::ReplaceObject(Engine3DRadSpace::IObject *obj, unsigned id)
{
	objects[id].second.reset(obj);
}

void Engine3DRadSpace::Game::ClearObjects()
{
	objects.clear();
}

void Engine3DRadSpace::Game::Load(Content::ContentManager *content)
{
	for(auto &[type, object] : objects)
	{
		object->Load(content);
	}
}

void Engine3DRadSpace::Game::Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt)
{
	for(auto &[type, object] : objects)
	{
		object->Update(keyboard, mouse, dt);
	}
}

void Engine3DRadSpace::Game::Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt)
{
	for(auto &[type, object] : objects)
	{
		if(type == 3u)
		{
			(static_cast<IObject3D *>(object.get()))->Draw(view, projection, dt);
		}
	}
}

void Engine3DRadSpace::Game::Draw(Graphics::SpriteBatch *spriteBatch, double dt)
{
	for(auto &[type, object] : objects)
	{
		if(type == 2u)
		{
			(static_cast<IObject2D *>(object.get()))->Draw(spriteBatch, dt);
		}
	}
}

void Engine3DRadSpace::Game::Initialize()
{
	for(auto &[type, object] : objects)
	{
		object->Initialize();
	}
}
