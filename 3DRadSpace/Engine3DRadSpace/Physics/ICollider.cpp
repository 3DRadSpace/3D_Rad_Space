#include "ICollider.hpp"
#include "IPhysicsEngine.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

ICollider::ICollider(IPhysicsEngine* physics) :
	IPhysicsActor(physics)
{
}