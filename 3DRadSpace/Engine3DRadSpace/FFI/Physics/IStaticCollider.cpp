#include "IStaticCollider.h"
#include "../../Physics/IStaticCollider.hpp"

using namespace Engine3DRadSpace::Physics;

float E3DRSP_IStaticCollider_GetLinearDamping(E3DRSP_IStaticCollider collider)
{
	if (collider == nullptr) return 0.0f;
	return static_cast<IStaticCollider*>(collider)->GetLinearDamping();
}

void E3DRSP_IStaticCollider_SetLinearDamping(E3DRSP_IStaticCollider collider, float linearDamping)
{
	if (collider == nullptr) return;
	static_cast<IStaticCollider*>(collider)->SetLinearDamping(linearDamping);
}

float E3DRSP_IStaticCollider_GetStaticFriction(E3DRSP_IStaticCollider collider)
{
	if (collider == nullptr) return 0.0f;
	return static_cast<IStaticCollider*>(collider)->GetStaticFriction();
}

void E3DRSP_IStaticCollider_SetStaticFriction(E3DRSP_IStaticCollider collider, float friction)
{
	if (collider == nullptr) return;
	static_cast<IStaticCollider*>(collider)->SetStaticFriction(friction);
}

float E3DRSP_IStaticCollider_GetDynamicFriction(E3DRSP_IStaticCollider collider)
{
	if (collider == nullptr) return 0.0f;
	return static_cast<IStaticCollider*>(collider)->GetDynamicFriction();
}

void E3DRSP_IStaticCollider_SetDynamicFriction(E3DRSP_IStaticCollider collider, float friction)
{
	if (collider == nullptr) return;
	static_cast<IStaticCollider*>(collider)->SetDynamicFriction(friction);
}

float E3DRSP_IStaticCollider_GetRestitution(E3DRSP_IStaticCollider collider)
{
	if (collider == nullptr) return 0.0f;
	return static_cast<IStaticCollider*>(collider)->GetRestitution();
}

void E3DRSP_IStaticCollider_SetRestitution(E3DRSP_IStaticCollider collider, float restitution)
{
	if (collider == nullptr) return;
	static_cast<IStaticCollider*>(collider)->SetRestitution(restitution);
}

void E3DRSP_IStaticCollider_Destroy(E3DRSP_IStaticCollider collider)
{
	if (collider == nullptr) return;
	delete static_cast<IStaticCollider*>(collider);
}
