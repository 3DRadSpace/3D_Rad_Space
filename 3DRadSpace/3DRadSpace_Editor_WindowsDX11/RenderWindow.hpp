#pragma once
#include "Engine3DRadSpace/Game.hpp"

class RenderWindow : public Engine3DRadSpace::Game
{
public:
	RenderWindow(Engine3DRadSpace::Window& w);

	void Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) override;
	void Draw(double dt) override;
};