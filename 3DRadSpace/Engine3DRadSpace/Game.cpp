#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Graphics;

Game::Game(const char* title, unsigned width, unsigned height, bool fullscreen) :
	Window(std::make_unique<Engine3DRadSpace::Window>(title, width, height))
{
	Device = std::make_unique<GraphicsDevice>(Window->NativeHandle(),width,height);
	Content = std::make_unique<Content::ContentManager>(Device.get());
	SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
	_valid = true;
}

Game::Game(Engine3DRadSpace::Window &&window) :
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

void Game::RunOneFrame()
{
	auto ts_u1 = std::chrono::high_resolution_clock::now();

	auto& keyboard = Window->GetKeyboardState();
	auto& mouse = Window->GetMouseState();

	Game::Update(keyboard, mouse, u_dt);
	this->Update(Window->GetKeyboardState(), Window->GetMouseState(), u_dt);
	auto ts_u2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
	u_dt = uDiff.count();

	auto ts_d1 = std::chrono::high_resolution_clock::now();

	this->Device->SetViewport();
	this->Device->Clear(ClearColor);

	Game::Draw(View, Projection, d_dt);
	this->Draw(View,Projection,d_dt);

	this->Device->Present();

	auto ts_d2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> dDiff = ts_d2 - ts_d1;
	d_dt = dDiff.count();
}

void Game::Exit()
{
	_running = false;
}


void Game::Load(Content::ContentManager* content)
{
	for (auto& [object, type] : Objects)
	{
		object->Load(content);
	}
}

void Game::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
	for (auto& [object, type] : Objects)
	{
		object->Update(keyboard, mouse, dt);
	}
}

void Game::Draw(Math::Matrix& view, Math::Matrix& projection, double dt)
{
	for (auto& [object, type] : Objects)
	{
		if (type == ObjectList::ObjectInstance::ObjectType::IObject3D)
		{
			(static_cast<IObject3D*>(object.get()))->Draw(view, projection, dt);
		}
	}
}

void Game::Draw(Graphics::SpriteBatch* spriteBatch, double dt)
{
	for (auto& [object, type] : Objects)
	{
		if (type == ObjectList::ObjectInstance::ObjectType::IObject2D)
		{
			(static_cast<IObject2D*>(object.get()))->Draw(spriteBatch, dt);
		}
	}
}

void Game::Initialize()
{
	for (auto& [object, type] : Objects)
	{
		object->Initialize();
	}
}
