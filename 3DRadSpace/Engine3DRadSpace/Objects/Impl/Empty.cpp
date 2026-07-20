#include "Empty.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Empty::Empty(const std::string& name, const Vector3& pos, const Vector3& pivot, const Quaternion& rot, const Vector3& scale) :
	IObject3D(name, true, true, pos, pivot, rot, scale)
{
}

void Empty::Initialize()
{
}

void Empty::Update()
{
}

void Empty::Load()
{
}

void Empty::Load(const std::filesystem::path& path)
{
}

Reflection::UUID Empty::GetUUID() const noexcept
{
	// {00000000-0000-0000-0000-000000000000}
	return { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
}

void Empty::Draw3D()
{
}

float Empty::Intersects(const Math::Ray& r)
{
	return std::numeric_limits<float>::signaling_NaN();
}

Gizmos::IGizmo* Empty::GetGizmo() const noexcept
{
	return nullptr;
}

REFL_BEGIN(Empty, "Empty", "Physics", "Represents a point")
	REFL_FIELD(Empty, std::string, Name, "Name", "Empty", "Object name")
	REFL_FIELD(Empty, Vector3, Position, "Position", Vector3::Zero(), "Object position in world space")
	REFL_FIELD(Empty, Quaternion, Rotation, "Rotation", Quaternion(), "Object rotation in world space")
	REFL_FIELD(Empty, Vector3, RotationCenter, "Rotation Center", Vector3::Zero(), "Rotation center/pivot")
	REFL_FIELD(Empty, Vector3, Scale, "Scale", Vector3::One(), "Object scale. 1 = original size")
	REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/Empty.html")
REFL_END