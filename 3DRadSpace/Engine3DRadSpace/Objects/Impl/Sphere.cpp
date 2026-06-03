#include "Sphere.hpp"
#include "../../Core/IGame.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Sphere::Sphere() : IObject3D("Sphere", false, true, Vector3::Zero()),
	Radius(1.0f),
	Resolution(64u)
{
}

void Sphere::Initialize()
{
}

void Sphere::Load()
{
	_sphere = std::make_unique<Primitives::Sphere>(GetGraphicsDeviceHandle(), 1.0f, Colour, Resolution);
}

void Sphere::Load(const std::filesystem::path& path)
{
	(void)path;
	Load();
}

void Sphere::Update()
{
}

void Sphere::Draw3D()
{
	if(_sphere && Visible)
	{
		auto game = static_cast<Game*>(_game);
		_sphere->Transform = this->GetModelMatrix();
		_sphere->View = game->View;
		_sphere->Projection = game->Projection;
		_sphere->Draw3D();
	}
}

float Sphere::Intersects(const Math::Ray& r)
{
	return r.Intersects(BoundingSphere(Position, Radius));
}

Math::Matrix4x4 Sphere::GetLocalMatrix()
{
	return Matrix4x4::CreateScale({Radius, Radius, Radius}) * Matrix4x4::CreateTranslation(Position);
}

Gizmos::IGizmo* Sphere::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Sphere>(this);
}

Reflection::UUID Sphere::GetUUID() const noexcept
{
	// {F7A76B8D-A2C4-47BE-8625-3B845507B979}
	return {0xf7a76b8d, 0xa2c4, 0x47be, { 0x86, 0x25, 0x3b, 0x84, 0x55, 0x7, 0xb9, 0x79 }};
}

Graphics::Primitives::Sphere* Sphere::GetPrimitive() const noexcept
{
	return _sphere.get();
}

REFL_BEGIN(Sphere, "Sphere", "3D Primitives", "3D box")
	REFL_FIELD(Sphere, std::string, Name, "Name", "Sphere", "Object's name")
	REFL_FIELD(Sphere, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(Sphere, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
	REFL_FIELD(Sphere, float, Radius, "Radius", 1.0f, "Radius")
	REFL_FIELD(Sphere, Color, Colour, "Color", Colors::White, "Color")
	REFL_FIELD(Sphere, unsigned, Resolution, "Resolution", 64, "Sphere model tesselation")
REFL_END