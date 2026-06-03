#include "Box.hpp"
#include "../../Core/IGame.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Box::Box() : IObject3D("Box", false, true, Vector3::Zero(), Vector3::Zero(), Quaternion(), Vector3::One())
{
}

void Box::Initialize()
{
}

void Box::Load()
{
	_box = std::make_unique<Primitives::Box>(GetGraphicsDeviceHandle(), BoundingBox({0,0,0}, {1,1,1}), Colour);
}

void Box::Load(const std::filesystem::path& path)
{
	(void)path;
	Load();
}

void Box::Update()
{
}

void Box::Draw3D()
{
	if(_box && Visible)
	{
		auto game = static_cast<Game*>(_game);
		_box->Transform = this->GetModelMatrix();
		_box->View = game->View;
		_box->Projection = game->Projection;
		_box->Draw3D();
	}
}

float Box::Intersects(const Math::Ray& r)
{
	return r.Intersects(BoundingBox(Position, Scale));
}

Gizmos::IGizmo* Box::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Box>(this);
}

Reflection::UUID Box::GetUUID() const noexcept
{
	// {70CE72A2-000C-4440-8DA9-C1F240C769E5}
	return {0x70ce72a2, 0xc, 0x4440, { 0x8d, 0xa9, 0xc1, 0xf2, 0x40, 0xc7, 0x69, 0xe5 }};
}

Graphics::Primitives::Box* Box::GetPrimitive() const noexcept
{
	return _box.get();
}

REFL_BEGIN(Box, "Box", "3D Primitives", "3D box")
	REFL_FIELD(Box, std::string, Name, "Name", "Skinmesh", "Object's name")
	REFL_FIELD(Box, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(Box, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
	REFL_FIELD(Box, Vector3, Scale, "Scale", Vector3::One(), "Scale")
	REFL_FIELD(Box, Color, Colour, "Color", Colors::White, "Color")
REFL_END