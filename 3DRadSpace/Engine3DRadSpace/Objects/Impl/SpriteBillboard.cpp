#include "SpriteBillboard.hpp"
#include "../../Content/ContentManager.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

SpriteBillboard::SpriteBillboard(
	const std::string& name,
	bool visible,
	const std::filesystem::path& texturePath,
	const Math::Vector3& pos,
	const Math::Vector3& axis,
	bool spherical
) : IObject3D(name, visible, visible, pos, axis), 
	IsSpherical(spherical)
{
	if (!texturePath.empty())
	{
		_tempPath = std::make_unique<std::filesystem::path>(texturePath);
	}
}

SpriteBillboard::SpriteBillboard(
	const std::string& name,
	bool visible,
	RefTexture2D resource,
	const Math::Vector3& pos,
	const Math::Vector3& axis,
	bool spherical
) : IObject3D(name, visible, visible, pos, axis),
	IsSpherical(spherical)
{
}

void SpriteBillboard::Initialize()
{
}

void SpriteBillboard::Load()
{
	if (_tempPath)
	{
		auto content = GetGame()->RequireService<Content::ContentManager>({});
		_texture = content->Load<Content::Assets::TextureAsset>(*_tempPath)->Get();

		_tempPath.reset();
	}
	else if (Texture)
	{
		auto content = GetGame()->RequireService<Content::ContentManager>({});
		_texture = content->operator[]<Content::Assets::TextureAsset>(Texture)->Get();
	}

	_createBillboard();
}

void SpriteBillboard::Load(const std::filesystem::path& path)
{
	auto content = GetGame()->RequireService<Content::ContentManager>({});
	_texture = content->Load<Content::Assets::TextureAsset>(path)->Get();

	_createBillboard();
}

void SpriteBillboard::_createBillboard()
{
	_cylindricalBillboard.reset();

	if (IsSpherical)
	{
		_cylindricalBillboard = std::make_unique<Graphics::Primitives::SphericalBillboard>(GetGraphicsDeviceHandle());
	}
	else
	{
		_cylindricalBillboard = std::make_unique<Graphics::Primitives::CylindricalBillboard>(GetGraphicsDeviceHandle());
	}
}

void SpriteBillboard::Update()
{
}

void SpriteBillboard::Draw3D()
{
	if (_texture && Visible)
	{
		_cylindricalBillboard->Axis = RotationCenter;
		_cylindricalBillboard->Position = Position;
		_cylindricalBillboard->Texture = _texture;
		_cylindricalBillboard->Scale = Vector2(Scale.X, Scale.Y);

		auto game = static_cast<Game*>(GetGame());
		_cylindricalBillboard->View = game->View;
		_cylindricalBillboard->Projection = game->Projection;

		_cylindricalBillboard->Draw3D();
	}
}

Reflection::UUID SpriteBillboard::GetUUID() const noexcept
{
	// {C083D382-86D9-40A0-AFCC-16109C9B0C35}
	return { 0xc083d382, 0x86d9, 0x40a0, { 0xaf, 0xcc, 0x16, 0x10, 0x9c, 0x9b, 0xc, 0x35 } };
}

float SpriteBillboard::Intersects(const Math::Ray& r)
{
	// Create a bounding box centered at the billboard's position
	BoundingBox box(Position - (Scale / 2), Scale);

	// Create a plane perpendicular to the billboard's axis passing through the billboard position
	// The normal of the plane is the billboard's axis (RotationCenter)
	BoundingPlane plane;
	plane.Normal = RotationCenter.Normalize();
	plane.D = -Vector3::Dot(plane.Normal, Position);

	// Check if ray intersects the plane
	float planeIntersection = r.Intersects(plane);
	if (std::isnan(planeIntersection))
		return std::numeric_limits<float>::signaling_NaN();

	// Check if ray intersects the bounding box
	float boxIntersection = r.Intersects(box);
	if (std::isnan(boxIntersection))
		return std::numeric_limits<float>::signaling_NaN();

	// Return the closer intersection distance
	return std::min(planeIntersection, boxIntersection);
}

Gizmos::IGizmo* SpriteBillboard::GetGizmo() const noexcept
{
	return Internal::GizmoOf<SpriteBillboard>(this);
}

REFL_BEGIN(SpriteBillboard, "SpriteBillboard", "3D Objects", "Renders sprites in world space")
REFL_FIELD(SpriteBillboard, std::string, Name, "Name", "SpriteBillboard", "Name of the object")
REFL_FIELD(SpriteBillboard, bool, Visible, "Enabled", true, "Whether the object is enabled or not")
REFL_FIELD(SpriteBillboard, RefTexture2D, Texture, "Texture", 0, "Reference to the texture resource")
REFL_FIELD(SpriteBillboard, Math::Vector3, Position, "Position", Math::Vector3::Zero(), "Position of the object in world space")
REFL_FIELD(SpriteBillboard, Math::Vector3, RotationCenter, "Axis", Math::Vector3::Zero(), "Axis of rotation for the object")
REFL_FIELD(SpriteBillboard, Math::Vector3, Scale, "Scale", Math::Vector3::One(), "Scale of the object in world space")
REFL_FIELD(SpriteBillboard, bool, IsSpherical, "Spherical", false, "Whether the billboard is spherical or cylindrical")
REFL_END