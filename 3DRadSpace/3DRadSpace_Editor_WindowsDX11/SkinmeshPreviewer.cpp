#include "SkinmeshPreviewer.hpp"
#include <Engine3DRadSpace/Objects/Skinmesh.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

SkinmeshPreviewer::SkinmeshPreviewer(const std::filesystem::path &meshPath):
	Game("Skinmesh previewer", 800, 600, false)
{
	AddObject(new Skinmesh("", true, "", meshPath));
}
