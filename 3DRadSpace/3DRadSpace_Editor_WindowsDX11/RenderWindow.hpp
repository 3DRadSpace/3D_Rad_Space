#pragma once
#include "Engine3DRadSpace/Game.hpp"
#include "Engine3DRadSpace/Shader_PosColor_NoMat.hpp"
#include "Engine3DRadSpace/VertexBuffer.hpp"

class RenderWindow : public Engine3DRadSpace::Game
{
	Engine3DRadSpace::Graphics::Shaders::Shader_PosColor_NoMatrix _triangleShader;
	std::unique_ptr<Engine3DRadSpace::Graphics::VertexBuffer<Engine3DRadSpace::Graphics::VertexPositionColor>> _triangleBuffer;
public:
	RenderWindow(HWND parent, HINSTANCE hInstance);

	void Initialize() override;
	void Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) override;
	void Draw(double dt) override;

	inline virtual ~RenderWindow() = default;
};