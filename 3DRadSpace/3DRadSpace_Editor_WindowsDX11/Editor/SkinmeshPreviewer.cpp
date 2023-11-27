#include "SkinmeshPreviewer.hpp"
#include <Engine3DRadSpace/Objects/Skinmesh.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

SkinmeshPreviewer::SkinmeshPreviewer(const std::filesystem::path &meshPath):
	Game((std::string("Skinmesh previewer - ") + meshPath.string()).c_str(), 800, 600, false)
{
	Objects.AddNew<Skinmesh>("", true, "", meshPath);
	
	_camera = new Camera();
	_camera->LookAt = Vector3::Zero();
	Objects.Add(_camera);
}

void SkinmeshPreviewer::Update(Keyboard &keyboard, Mouse &mouse, double dt)
{
	if(mouse.LeftButton() == ButtonState::Pressed)
	{
		
	}
}
