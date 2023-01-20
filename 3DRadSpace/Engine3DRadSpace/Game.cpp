#include "Game.hpp"
#include <chrono>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;

Game::Game(const char* title, int width, int height, bool fullscreen) :
	window(std::make_unique<Window>(title, width, height))
{
	device = std::make_unique<GraphicsDevice>(window->NativeHandle(),width,height);
}

void Game::Run()
{
	float u_dt = 0;
	float d_dt = 0;
	while (true)
	{	
		Keyboard keyboard{};
		Mouse mouse{};

		std::chrono::high_resolution_clock c1;

		auto u1 = c1.now();
		window->ProcessFrame();
		this->Update(keyboard,mouse, u_dt);
		auto u2 = c1.now();

		u_dt = (u1 - u2).count();

		this->Draw(device.get(),d_dt);
	}
}
