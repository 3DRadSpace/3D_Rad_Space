#include "SphereGizmo.hpp"

using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<Sphere>::Gizmo()
{
	AllowRotating = false;
	AllowScaling = false;
	Allow2DRendering = false;
}

void Gizmo<Sphere>::Load()
{
	if(Object != nullptr)
	{
		Object->Initialize();
		Object->Load();
	}
}

void Gizmo<Sphere>::Load(const std::filesystem::path& path)
{
	if(Object != nullptr)
	{
		Object->Load(path);
	}
}

void Gizmo<Sphere>::Draw3D()
{
	if(!Allow3DRendering) return;

	if(Object != nullptr)
	{
		auto obj = dynamic_cast<IObject3D*>(Object);
		if(obj != nullptr)
		{
			obj->Draw3D();
		}
	}
}

void Gizmo<Sphere>::Draw2D()
{
	// Sphere doesn't support 2D rendering
}

void Gizmo<Sphere>::Update()
{
	if(!AllowUpdating) return;

	if(Object != nullptr)
	{
		Object->Update();
	}
}
