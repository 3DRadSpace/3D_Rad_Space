#pragma once
#include "Engine3DRadSpace/Game.hpp"
#include "Engine3DRadSpace/Graphics/VertexBuffer.hpp"
#include <Engine3DRadSpace/Graphics/Shaders/BlankShader.hpp>
#include <Engine3DRadSpace\Math\Matrix4x4.hpp>
#include <Engine3DRadSpace/Math/Vector2.hpp>
#include <Engine3DRadSpace/Objects/Camera.hpp>
#include <Engine3DRadSpace/Graphics/Model3D.hpp>
#include <Engine3DRadSpace/Graphics/Shaders/BasicTextured.hpp>
#include <Engine3DRadSpace/Graphics/SpriteBatch.hpp>
#include <Engine3DRadSpace/Graphics/Primitives/Lines.hpp>
#include <Engine3DRadSpace/Graphics/Fonts/Font.hpp>
#include <Engine3DRadSpace/Graphics/Fonts/FontShader.hpp>
#include <Engine3DRadSpace/Algorithms/Picking/PickingRenderTargetRender.hpp>

class RenderWindow : public Engine3DRadSpace::Game
{
	Engine3DRadSpace::Math::Vector2 cameraPos =
	{
		cosf(std::numbers::pi_v<float> / 6), //30 degrees = pi/6 radians
		sinf(std::numbers::pi_v<float> / 6)
	};

	Engine3DRadSpace::Math::Vector3 cursor3D = Engine3DRadSpace::Math::Vector3::Zero();

	HWND editorWindow;
	Engine3DRadSpace::Objects::Camera Camera;
	std::unique_ptr<Engine3DRadSpace::Graphics::Primitives::Lines> lines;

	float zoom = 5.0f;
	float timer = 0;

	std::unique_ptr<Engine3DRadSpace::Graphics::Shaders::BasicTextured> texturedShader;
	std::unique_ptr<Engine3DRadSpace::Graphics::SamplerState> samplerState;

	Engine3DRadSpace::Graphics::Texture2D* testTexture;
	std::unique_ptr<Engine3DRadSpace::Algorithms::Picking::PickingShader> _pickingShader;

	bool _keyboardTest = false;

	std::unique_ptr<Engine3DRadSpace::Graphics::Fonts::Font> testFont;
	std::unique_ptr<Engine3DRadSpace::Graphics::Fonts::FontShader> fontShader;
	std::unique_ptr<Engine3DRadSpace::Graphics::VertexBufferV<Engine3DRadSpace::Graphics::VertexPointUV>> fontBuff;
public:
	RenderWindow(HWND parent, HINSTANCE hInstance);

	void Initialize() override;
	void Load(Engine3DRadSpace::Content::ContentManager *content) override;
	void Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) override;
	void Draw(
		Engine3DRadSpace::Math::Matrix4x4 &view,
		Engine3DRadSpace::Math::Matrix4x4 &projection,
		double dt) override;

	bool IsFocused();
	void Reset3DCursor();
};