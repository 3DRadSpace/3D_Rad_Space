#pragma once
#include "IStaticCollider.h"
#include "../Math/Vector3.h"
#include "../Math/BoundingBox.h"
#include "../Math/BoundingSphere.h"

typedef void* E3DRSP_IDynamicCollider;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT float E3DRSP_IDynamicCollider_GetAngularDamping(E3DRSP_IDynamicCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_SetAngularDamping(E3DRSP_IDynamicCollider collider, float angularDamping);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_IDynamicCollider_GetLinearVelocity(E3DRSP_IDynamicCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_SetLinearVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* linearVelocity);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_IDynamicCollider_GetAngularVelocity(E3DRSP_IDynamicCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_SetAngularVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* angularVelocity);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_IDynamicCollider_GetMaxAngularVelocity(E3DRSP_IDynamicCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_SetMaxAngularVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* linearVelocity);

	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_AttachShapeBox(E3DRSP_IDynamicCollider collider, const E3DRSP_BoundingBox* box);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_AttachShapeSphere(E3DRSP_IDynamicCollider collider, const E3DRSP_BoundingSphere* sphere);

	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_UpdateMassAndInertia(E3DRSP_IDynamicCollider collider);

	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_ApplyForce(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* force);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_ApplyForceAtCenter(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* force, const E3DRSP_Vector3* center);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_ApplyTorque(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* force);

	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_ApplyAcceleration(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* acc);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_ApplyAngularAcceleration(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* acc);

	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_SetKinematic(E3DRSP_IDynamicCollider collider, bool isKinematic);

	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_AddLinearVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* v);
	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_AddAngularVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* v);

	E3DRSP_FFI_EXPORT void E3DRSP_IDynamicCollider_Destroy(E3DRSP_IDynamicCollider collider);
#ifdef __cplusplus
}
#endif
