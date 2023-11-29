#pragma once
#include <Engine3DRadSpace/Game.hpp>

namespace Engine3DRadSpace::Objects
{
	class Camera;
	class Skinmesh;
}

class SkinmeshPreviewer : public Engine3DRadSpace::Game
{
	Engine3DRadSpace::Objects::Camera *_camera;
	std::unique_ptr<Engine3DRadSpace::Objects::Skinmesh> _skinmesh;
	std::shared_ptr<Engine3DRadSpace::Graphics::Shaders::BasicTextured> _basicShader;
	float _zoom;
	float _initialZoom;
	Engine3DRadSpace::Math::Vector2 _camCoords =
	{
		cosf(std::numbers::pi_v<float> / 6), //30 degrees = pi/6 radians
		sinf(std::numbers::pi_v<float> / 6)
	};
public:
	explicit SkinmeshPreviewer(HWND owner, HINSTANCE hInstance, const std::filesystem::path& modelPath);

	SkinmeshPreviewer(SkinmeshPreviewer &) = delete;
	SkinmeshPreviewer &operator=(SkinmeshPreviewer &) = delete;

	void Update(Engine3DRadSpace::Input::Keyboard &keyboard, Engine3DRadSpace::Input::Mouse &mouse, double dt) override;
	void Draw(Engine3DRadSpace::Math::Matrix4x4& view, Engine3DRadSpace::Math::Matrix4x4& projection, double dt) override;
};

