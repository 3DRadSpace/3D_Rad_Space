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
	this->Initialize();
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
