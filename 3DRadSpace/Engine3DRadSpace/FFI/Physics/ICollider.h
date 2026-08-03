#pragma once
#include "IPhysicsEngine.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Math/Ray.h"

typedef void* E3DRSP_ICollider;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT float E3DRSP_ICollider_GetMass(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetMass(E3DRSP_ICollider* collider, float mass);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_ICollider_GetPosition(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetPosition(E3DRSP_ICollider* collider, const E3DRSP_Vector3* position);

	E3DRSP_FFI_EXPORT E3DRSP_Quaternion E3DRSP_ICollider_GetRotation(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetRotation(E3DRSP_ICollider* collider, const E3DRSP_Quaternion* rotation);

	E3DRSP_FFI_EXPORT float E3DRSP_ICollider_GetLinearDamping(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetLinearDamping(E3DRSP_ICollider* collider, float linearDamping);

	E3DRSP_FFI_EXPORT float E3DRSP_ICollider_GetAngularDamping(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetAngularDamping(E3DRSP_ICollider* collider, float angularDamping);

	E3DRSP_FFI_EXPORT float E3DRSP_ICollider_GetStaticFriction(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetStaticFriction(E3DRSP_ICollider* collider, float staticFriction);

	E3DRSP_FFI_EXPORT float E3DRSP_ICollider_GetDynamicFriction(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetDynamicFriction(E3DRSP_ICollider* collider, float dynFriction);

	E3DRSP_FFI_EXPORT float E3DRSP_ICollider_GetRestitution(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetRestitution(E3DRSP_ICollider* collider, float restitution);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_ICollider_GetLinearVelocity(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetLinearVelocity(E3DRSP_ICollider* collider, const E3DRSP_Vector3* vel);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_ICollider_GetAngularVelocity(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetAngularVelocity(E3DRSP_ICollider* collider, const E3DRSP_Vector3* vel);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_ICollider_GetMaxAngularVelocity(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_SetMaxAngularVelocity(E3DRSP_ICollider* collider, const E3DRSP_Vector3* vel);

	E3DRSP_FFI_EXPORT E3DRSP_IPhysicsEngine E3DRSP_ICollider_GetPhysics(const E3DRSP_ICollider* collider);

	E3DRSP_FFI_EXPORT bool E3DRSP_ICollider_ApplyForce(E3DRSP_ICollider* collider, const E3DRSP_Vector3* force);
	E3DRSP_FFI_EXPORT bool E3DRSP_ICollider_ApplyForce2(E3DRSP_ICollider* collider, const E3DRSP_Vector3* force, const E3DRSP_Vector3* center);
	E3DRSP_FFI_EXPORT bool E3DRSP_ICollider_ApplyTorque(E3DRSP_ICollider* collider, const E3DRSP_Vector3* force);

	E3DRSP_FFI_EXPORT bool E3DRSP_ICollider_ApplyAcceleration(E3DRSP_ICollider* collider, E3DRSP_Vector3* acc);
	E3DRSP_FFI_EXPORT bool E3DRSP_ICollider_ApplyAngularAcceleration(E3DRSP_ICollider* collider, E3DRSP_Vector3* acc);

	E3DRSP_FFI_EXPORT float E3DRSP_ICollider_Intersects(E3DRSP_ICollider* collider, const E3DRSP_Ray* r);

	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_UpdateTransform(E3DRSP_ICollider* collider);
	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_UpdateTransform2(E3DRSP_ICollider* collider, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation);

	E3DRSP_FFI_EXPORT void E3DRSP_ICollider_Destroy(E3DRSP_ICollider* collider);
#ifdef __cplusplus
}
#endif