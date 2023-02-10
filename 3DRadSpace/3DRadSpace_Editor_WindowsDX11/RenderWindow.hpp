#pragma once
#include "Engine3DRadSpace/Game.hpp"
#include "Engine3DRadSpace/TrivialPixelShader.hpp"

class RenderWindow : public Engine3DRadSpace::Game
{
	Engine3DRadSpace::Graphics::Shaders::TrivialPixelShader _triangleShader;
public:
	RenderWindow(Engine3DRadSpace::Window* w);

	void Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) override;
	void Draw(double dt) override;

	inline virtual ~RenderWindow() = default;
};