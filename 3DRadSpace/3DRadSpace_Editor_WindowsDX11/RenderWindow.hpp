#pragma once
#include "Engine3DRadSpace/Game.hpp"
#include "Engine3DRadSpace/VertexBuffer.hpp"
#include <Engine3DRadSpace/BlankShader.hpp>
#include <Engine3DRadSpace/Matrix.hpp>
#include <Engine3DRadSpace/Vector2.hpp>

class RenderWindow : public Engine3DRadSpace::Game
{
	std::unique_ptr<Engine3DRadSpace::Graphics::Shaders::BlankShader> simpleShader;
	std::unique_ptr<Engine3DRadSpace::Graphics::VertexBuffer<Engine3DRadSpace::Graphics::VertexPositionColor>> lines;

	Engine3DRadSpace::Math::Vector2 cameraPos;

	HWND editorWindow;
public:
	RenderWindow(HWND parent, HINSTANCE hInstance);

	void Initialize() override;
	void Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) override;
	void Draw(
		Engine3DRadSpace::Math::Matrix &view,
		Engine3DRadSpace::Math::Matrix &projection,
		double dt) override;

	bool IsFocused();
};