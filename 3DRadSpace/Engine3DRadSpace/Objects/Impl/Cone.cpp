#include "Cone.hpp"
#include "../../Core/IGame.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Cone::Cone() : IObject3D("Cone", false, true, Vector3::Zero()),
	Radius(1.0f),
	Height(1.0f),
	Resolution(64u)
{
}

void Cone::Initialize()
{
}

void Cone::Load()
{
	_cone = std::make_unique<Primitives::Cone>(GetGraphicsDeviceHandle(), 1.0f, 1.0f, Resolution, Colour);
}

void Cone::Load(const std::filesystem::path& path)
{
	(void)path;
	Load();
}

void Cone::Update()
{
}

void Cone::Draw3D()
{
	if(_cone && Visible)
	{
		auto game = static_cast<Game*>(_game);
		_cone->Transform = this->GetModelMatrix();
		_cone->View = game->View;
		_cone->Projection = game->Projection;
		_cone->Draw3D();
	}
}

float Cone::Intersects(const Math::Ray& r)
{
	return r.Intersects(BoundingSphere(Position, Radius));
}

Math::Matrix4x4 Cone::GetLocalMatrix()
{
	return Matrix4x4::CreateScale({Radius, Height, Radius}) * Matrix4x4::CreateFromQuaternion(Rotation) * Matrix4x4::CreateTranslation(Position);
}

Gizmos::IGizmo* Cone::GetGizmo() const noexcept
{
	auto gizmo =  Internal::GizmoOf<Cone>(this);
	gizmo->Allow3DRendering = true;
	gizmo->AllowScaling = false;
	gizmo->AllowRotating = true;
	gizmo->AllowTranslating = true;

	return gizmo;
}

Reflection::UUID Cone::GetUUID() const noexcept
{
	// {1260D6C2-FDD3-41A3-949E-AC2FD647253C}
	return {0x1260d6c2, 0xfdd3, 0x41a3, { 0x94, 0x9e, 0xac, 0x2f, 0xd6, 0x47, 0x25, 0x3c }};
}

Graphics::Primitives::Cone* Cone::GetPrimitive() const noexcept
{
	return _cone.get();
}

REFL_BEGIN(Cone, "Cone", "3D Primitives", "3D box")
	REFL_FIELD(Cone, std::string, Name, "Name", "Cone", "Object's name")
	REFL_FIELD(Cone, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(Cone, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
	REFL_FIELD(Cone, Quaternion, Rotation, "Rotation", Quaternion(), "Object's rotation in world space")
	REFL_FIELD(Cone, float, Radius, "Radius", 1.0f, "Scale")
	REFL_FIELD(Cone, float, Height, "Height", 1.0f, "Scale")
	REFL_FIELD(Cone, Color, Colour, "Color", Colors::White, "Color")
	REFL_FIELD(Cone, unsigned, Resolution, "Resolution", 64, "Sphere model tesselation")
	REFL_METHOD(Cone, void, &Cone::Show, "Show")
	REFL_METHOD(Cone, void, &Cone::Hide, "Hide")
	REFL_METHOD(Cone, bool, &Cone::SwitchVisibility, "Switch Visibility")
	REFL_ATTR("HelpURL","https://3dradspace.github.io/docs/Cone.html")
REFL_END