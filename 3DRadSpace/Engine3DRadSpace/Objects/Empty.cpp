#include "Empty.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Empty::Empty(const std::string& name, const std::string& tag, const Vector3& pos, const Vector3& pivot, const Quaternion& rot, const Vector3& scale) :
	IObject3D(name, tag, true, true, pos, pivot, rot, scale)
{
}

void Empty::Initialize()
{
}

void Empty::Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt)
{
}

void Empty::Load(Content::ContentManager* content)
{
}

void Empty::Load(Content::ContentManager* content, const std::filesystem::path& path)
{
}

void Empty::EditorInitialize()
{
}

void Empty::EditorLoad(Content::ContentManager* content)
{
}

Reflection::UUID Empty::GetUUID()
{
	// {408DFC5D-C1E7-4482-8040-B3C8369E75EC}
	return { 0x408dfc5d, 0xc1e7, 0x4482, { 0x80, 0x40, 0xb3, 0xc8, 0x36, 0x9e, 0x75, 0xec } };
}

void Empty::Draw(Math::Matrix4x4& view, Math::Matrix4x4& projection, double dt)
{
}

void Empty::EditorDraw(const Math::Matrix4x4& view, const Math::Matrix4x4& projection, double dt, bool selected)
{
}

std::optional<float> Empty::Intersects(const Math::Ray& r)
{
	return std::nullopt;
}

REFL_BEGIN(Empty, "Empty", "Physics", "Represents a point")
	REFL_FIELD(Empty, std::string, Name, "Name", "Empty", "Object name")
	REFL_FIELD(Empty, Vector3, Position, "Position", Vector3::Zero(), "Object position in world space")
	REFL_FIELD(Empty, Quaternion, Rotation, "Rotation", Quaternion(), "Object rotation in world space")
	REFL_FIELD(Empty, Vector3, RotationCenter, "Rotation Center", Vector3::Zero(), "Rotation center/pivot")
	REFL_FIELD(Empty, Vector3, Scale, "Scale", Vector3::One(), "Object scale. 1 = original size")
REFL_END