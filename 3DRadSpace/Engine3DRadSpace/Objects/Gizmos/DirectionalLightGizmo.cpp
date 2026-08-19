#include "DirectionalLightGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<DirectionalLight>::Gizmo() : IGizmo(true, false, true, false, true, false)
{
	rotation = Math::Quaternion();
}

void Gizmo<DirectionalLight>::Draw3D()
{
}

void Gizmo<DirectionalLight>::Draw2D()
{
}

void Gizmo<DirectionalLight>::Load()
{
	auto dirLight = dynamic_cast<DirectionalLight*>(Object);
	if (dirLight) dirLight->Initialize();
}

void Gizmo<DirectionalLight>::Load(const std::filesystem::path& path)
{
	Load();
}

void Gizmo<DirectionalLight>::Update()
{
	auto dirLight = dynamic_cast<DirectionalLight*>(Object);
	if (dirLight) dirLight->Update();
}