#include "GForce.hpp"
#include "../Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

GForce::GForce(const std::string& name, bool enabled, const std::string& tag, const Math::Vector3& gravity) :
    IObject(name, tag, enabled, false),
    Gravity(gravity)
{
}

void GForce::Initialize()
{
    if(Enabled)
        _game->RequestPhysicsInitialization(Gravity);
}

void GForce::Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt)
{
}

void GForce::Load(Content::ContentManager* content)
{
}

void GForce::Load(Content::ContentManager* content, const std::filesystem::path &path)
{
}

void GForce::EditorInitialize()
{
}

void GForce::EditorLoad(Content::ContentManager* content)
{
}

Reflection::UUID GForce::GetUUID()
{
    // {F671F8DA-03D9-4273-B88E-A0C15A18ACEB}
    return { 0xf671f8da, 0x3d9, 0x4273, { 0xb8, 0x8e, 0xa0, 0xc1, 0x5a, 0x18, 0xac, 0xeb } };
}

REFL_BEGIN(GForce, "G-Force", "Physics", "Enables physics and sets gravity")
    REFL_FIELD(GForce, std::string, Name, "Name", "G-Force", "Object name")
    REFL_FIELD(GForce, bool, Enabled, "Enabled", true, "Enables physics")
    REFL_FIELD(GForce, Vector3, Gravity, "Gravity", Vector3(0, -9.81f, 0), "Gravity value")
REFL_END
