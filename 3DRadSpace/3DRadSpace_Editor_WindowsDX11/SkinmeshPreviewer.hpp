#pragma once
#include <Engine3DRadSpace/Game.hpp>

class SkinmeshPreviewer : public Engine3DRadSpace::Game
{
public:
	SkinmeshPreviewer(const std::filesystem::path& modelPath);

	SkinmeshPreviewer(SkinmeshPreviewer &) = delete;
	SkinmeshPreviewer &operator=(SkinmeshPreviewer &) = delete;
};

