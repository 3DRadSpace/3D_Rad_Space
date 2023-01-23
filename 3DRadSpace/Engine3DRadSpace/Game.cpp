#include "Game.hpp"
#include <chrono>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;

Game::Game(const char* title, int width, int height, bool fullscreen) :
	Window(std::make_unique<Engine3DRadSpace::Window>(title, width, height))
{
	Device = std::make_unique<Engine3DRadSpace::GraphicsDevice>(Window->NativeHandle(),width,height);
}

Engine3DRadSpace::Game::Game(Engine3DRadSpace::Window& window)
{
	this->Window = std::make_unique<Engine3DRadSpace::Window>(window);
	Math::Point size = window.Size();

	this->Device = std::make_unique<GraphicsDevice>(window.NativeHandle(), size.X, size.Y);
}

void Game::Run()
{
	while (true)
	{	
		RunOneFrame();
	}
}

void Engine3DRadSpace::Game::RunOneFrame()
{
	double u_dt = 0;
	double d_dt = 0;

	auto ts_u1 = std::chrono::steady_clock::now();
	Window->ProcessMessages();
	this->Update(Window->GetKeyboardState(), Window->GetMouseState(), u_dt);
	auto ts_u2 = std::chrono::steady_clock::now();

	std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
	u_dt = uDiff.count();

	auto ts_d1 = std::chrono::steady_clock::now();

	this->Device->Clear();
	this->Draw(d_dt);

	this->Device->SetViewport(Viewport(this->Window->RectangleF(), 0.0f, 1.0f));
	this->Device->Present();

	auto ts_d2 = std::chrono::steady_clock::now();

	std::chrono::duration<double> dDiff = ts_d2 - ts_d1;
	d_dt = dDiff.count();
}
