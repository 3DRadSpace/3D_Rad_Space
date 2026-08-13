#include "SpriteGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<Sprite>::Gizmo()
{
	Allow3DRendering = false;
}

void Gizmo<Sprite>::Load()
{
	if(Object != nullptr)
	{
		Object->Initialize();
		Object->Load();
	}
}

void Gizmo<Sprite>::Load(const std::filesystem::path& path)
{
}

void Gizmo<Sprite>::Draw2D()
{
	if (Object == nullptr) return;

	auto sprite = static_cast<Sprite*>(Object);
	if (Selected)
	{
		auto oldTintColor = sprite->TintColor;
		sprite->TintColor = Color(1.0f, 0.5f, 0.0f, 1.0f);
		sprite->Draw2D();
		sprite->TintColor = oldTintColor;
	}
	else sprite->Draw2D();
}

void Gizmo<Sprite>::Draw3D()
{
}

void Gizmo<Sprite>::Update()
{
}
