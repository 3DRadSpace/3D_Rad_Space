#pragma once
#include "Engine3DRadSpace/Game.hpp"
#include "Engine3DRadSpace/VertexBuffer.hpp"
#include <Engine3DRadSpace/BlankShader.hpp>
#include <Engine3DRadSpace/Matrix.hpp>
#include <Engine3DRadSpace/Vector2.hpp>
#include <Engine3DRadSpace/Camera.hpp>

class RenderWindow : public Engine3DRadSpace::Game
{
	std::unique_ptr<Engine3DRadSpace::Graphics::Shaders::BlankShader> simpleShader;
	std::unique_ptr<Engine3DRadSpace::Graphics::VertexBufferV<Engine3DRadSpace::Graphics::VertexPositionColor>> lines;

	Engine3DRadSpace::Math::Vector2 cameraPos = 
		{ 
			cosf(std::numbers::pi_v<float> / 6), //30 degrees = pi/6 radians
			sinf(std::numbers::pi_v<float> / 6)
		};

	Engine3DRadSpace::Math::Vector3 cursor3D = Engine3DRadSpace::Math::Vector3::Zero();

	HWND editorWindow;

	Engine3DRadSpace::Objects::Camera Camera;

	std::unique_ptr<Engine3DRadSpace::RasterizerState> lineRasterizer;
	std::unique_ptr<Engine3DRadSpace::RasterizerState> defaultRasterizer;

	float zoom = 5.0f;
	float timer = 0;
public:
	RenderWindow(HWND parent, HINSTANCE hInstance);

	void Initialize() override;
	void Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) override;
	void Draw(
		Engine3DRadSpace::Math::Matrix &view,
		Engine3DRadSpace::Math::Matrix &projection,
		double dt) override;

	bool IsFocused();
	void Reset3DCursor();
};