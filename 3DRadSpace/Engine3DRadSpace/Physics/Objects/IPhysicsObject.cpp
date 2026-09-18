#include "IPhysicsObject.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;

IPhysicsObject::IPhysicsObject(
	const std::string& name,
	bool enabled,
	bool visible,
	const Math::Vector3& position,
	const Math::Quaternion& rotation,
	const Math::Vector3& scale
) : IObject3D(name, enabled, visible, position, Vector3::Zero(), rotation, scale),
	_physics(nullptr)
{
}

void IPhysicsObject::Initialize()
{
	_physics = static_cast<IPhysicsEngine*>(_game->RequireService(typeid(IPhysicsEngine)));
}

IPhysicsEngine* IPhysicsObject::GetPhysicsEngine() const noexcept
{
	return _physics;
}