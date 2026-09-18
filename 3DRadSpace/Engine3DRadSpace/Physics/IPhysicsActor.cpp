#include "IPhysicsActor.hpp"

using namespace Engine3DRadSpace::Physics;

IPhysicsActor::IPhysicsActor(IPhysicsEngine* physics) : _physics(physics)
{
}

IPhysicsEngine* IPhysicsActor::GetPhysics() const noexcept
{
	return _physics;
}