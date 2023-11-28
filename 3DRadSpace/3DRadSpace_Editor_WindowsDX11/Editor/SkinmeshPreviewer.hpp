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
	float _zoom;
	float _initialZoom;
	Engine3DRadSpace::Math::Vector2 _camCoords = { 0,0 };
public:
	explicit SkinmeshPreviewer(const std::filesystem::path& modelPath);

	SkinmeshPreviewer(SkinmeshPreviewer &) = delete;
	SkinmeshPreviewer &operator=(SkinmeshPreviewer &) = delete;

	void Update(Engine3DRadSpace::Input::Keyboard &keyboard, Engine3DRadSpace::Input::Mouse &mouse, double dt) override;
	void Draw(Math::Matrix4x4& view, Math::Matrix4x4& projection, double dt) override;
};

