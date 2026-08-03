#include "../../Physics/IPhysicsEngine.hpp"
#include "../../Physics/IStaticCollider.hpp"
#include "../../Physics/IDynamicCollider.hpp"
#include "../../Physics/ICharacterController.hpp"
#include "../../Physics/IJoint.hpp"
#include "../../Graphics/Model3D.hpp"
#include "IPhysicsEngine.h"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Graphics;

void E3DRSP_IPhysicsEngine_Simulate(E3DRSP_IPhysicsEngine* physics, float dt)
{
	reinterpret_cast<IPhysicsEngine*>(physics)->Simulate(dt);
}

void* E3DRSP_IPhysicsEngine_GetScene(E3DRSP_IPhysicsEngine* physics)
{
	return reinterpret_cast<IPhysicsEngine*>(physics)->GetScene();
}

E3DRSP_IStaticCollider E3DRSP_IPhysicsEngine_CreateStaticCollider(
	E3DRSP_IPhysicsEngine* physics,
	E3DRSP_Model3D model,
	const E3DRSP_Vector3* position,
	const E3DRSP_Quaternion* rotation,
	const E3DRSP_Vector3* scale
)
{
	if (physics == nullptr) return nullptr;

	Vector3 pos = position ? Vector3(position->X, position->Y, position->Z) : Vector3::Zero();
	Quaternion rot = rotation ? Quaternion(rotation->X, rotation->Y, rotation->Z, rotation->W) : Quaternion();
	Vector3 scl = scale ? Vector3(scale->X, scale->Y, scale->Z) : Vector3::One();

	auto collider = reinterpret_cast<IPhysicsEngine*>(physics)->CreateStaticCollider(
		static_cast<Model3D*>(model),
		pos,
		rot,
		scl
	);

	return collider.release();
}

E3DRSP_IDynamicCollider E3DRSP_IPhysicsEngine_CreateDynamicCollider(E3DRSP_IPhysicsEngine* physics)
{
	if (physics == nullptr) return nullptr;
	auto collider = reinterpret_cast<IPhysicsEngine*>(physics)->CreateDynamicCollider();
	return collider.release();
}

E3DRSP_ICharacterController E3DRSP_IPhysicsEngine_CreateCharacterController(
	E3DRSP_IPhysicsEngine* physics,
	float radius,
	float height,
	const E3DRSP_Vector3* position
)
{
	if (physics == nullptr) return nullptr;
	Vector3 pos = position ? Vector3(position->X, position->Y, position->Z) : Vector3::Zero();
	auto controller = reinterpret_cast<IPhysicsEngine*>(physics)->CreateCharacterController(radius, height, pos);
	return controller.release();
}

E3DRSP_IJoint E3DRSP_IPhysicsEngine_CreateJoint(E3DRSP_IPhysicsEngine* physics, E3DRSP_JointType type)
{
	if (physics == nullptr) return nullptr;
	auto joint = reinterpret_cast<IPhysicsEngine*>(physics)->CreateJoint(static_cast<JointType>(type));
	return joint.release();
}

double E3DRSP_IPhysicsEngine_GetDT(E3DRSP_IPhysicsEngine* physics)
{
	if (physics == nullptr) return 0.0;
	return reinterpret_cast<IPhysicsEngine*>(physics)->dt();
}

void E3DRSP_IPhysicsEngine_SetGravity(E3DRSP_IPhysicsEngine* physics, const E3DRSP_Vector3* gravity)
{
	if (physics == nullptr || gravity == nullptr) return;
	reinterpret_cast<IPhysicsEngine*>(physics)->SetGravity(Vector3(gravity->X, gravity->Y, gravity->Z));
}

E3DRSP_Vector3 E3DRSP_IPhysicsEngine_GetGravity(E3DRSP_IPhysicsEngine* physics)
{
	if (physics == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto gravity = reinterpret_cast<IPhysicsEngine*>(physics)->GetGravity();
	return E3DRSP_Vector3{ gravity.X, gravity.Y, gravity.Z };
}