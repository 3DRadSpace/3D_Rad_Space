#include "GForce.hpp"
#include "../IPhysicsEngine.hpp"
#include "../../Core/IGame.hpp"
#include "../../Objects/Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics::Objects;
using namespace Engine3DRadSpace::Reflection;

GForce::GForce(const std::string& name, bool enabled, const Math::Vector3& gravity) :
    IObject(name, enabled, false),
    Gravity(gravity)
{
}

void GForce::Initialize()
{
    auto* physics = static_cast<IPhysicsEngine*>(_game->RequireService(typeid(IPhysicsEngine)));
    if(physics && Enabled)
        physics->SetGravity(Gravity);
}

void GForce::Update()
{
}

void GForce::Load()
{
}

void GForce::Load(const std::filesystem::path &path)
{
}

Reflection::UUID GForce::GetUUID() const noexcept
{
    // {F671F8DA-03D9-4273-B88E-A0C15A18ACEB}
    return { 0xf671f8da, 0x3d9, 0x4273, { 0xb8, 0x8e, 0xa0, 0xc1, 0x5a, 0x18, 0xac, 0xeb } };
}

Gizmos::IGizmo* GForce::GetGizmo() const noexcept
{
    //return Internal::GizmoOf<GForce>(this);
    return nullptr;
}

REFL_BEGIN(GForce, "G-Force", "Physics", "Enables physics and sets gravity")
    REFL_FIELD(GForce, std::string, Name, "Name", "G-Force", "Object name")
    REFL_FIELD(GForce, bool, Enabled, "Enabled", true, "Enables physics")
    REFL_FIELD(GForce, Vector3, Gravity, "Gravity", Vector3(0, -9.81f, 0), "Gravity value")
	REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/GForce.html")
REFL_END