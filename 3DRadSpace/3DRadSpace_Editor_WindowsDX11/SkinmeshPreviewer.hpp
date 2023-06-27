#pragma once
#include <Engine3DRadSpace/Game.hpp>
#include <Engine3DRadSpace/Objects/Camera.hpp>

class SkinmeshPreviewer : public Engine3DRadSpace::Game
{
	Engine3DRadSpace::Objects::Camera *_camera;
public:
	SkinmeshPreviewer(const std::filesystem::path& modelPath);

	SkinmeshPreviewer(SkinmeshPreviewer &) = delete;
	SkinmeshPreviewer &operator=(SkinmeshPreviewer &) = delete;
};

