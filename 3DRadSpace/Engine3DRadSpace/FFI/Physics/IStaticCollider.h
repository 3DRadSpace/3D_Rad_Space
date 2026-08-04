#pragma once
#include "ICollider.h"
#include "../Math/Vector3.h"

typedef void* E3DRSP_IStaticCollider;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT float E3DRSP_IStaticCollider_GetLinearDamping(E3DRSP_IStaticCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IStaticCollider_SetLinearDamping(E3DRSP_IStaticCollider collider, float linearDamping);

	E3DRSP_FFI_EXPORT float E3DRSP_IStaticCollider_GetStaticFriction(E3DRSP_IStaticCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IStaticCollider_SetStaticFriction(E3DRSP_IStaticCollider collider, float friction);

	E3DRSP_FFI_EXPORT float E3DRSP_IStaticCollider_GetDynamicFriction(E3DRSP_IStaticCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IStaticCollider_SetDynamicFriction(E3DRSP_IStaticCollider collider, float friction);

	E3DRSP_FFI_EXPORT float E3DRSP_IStaticCollider_GetRestitution(E3DRSP_IStaticCollider collider);
	E3DRSP_FFI_EXPORT void E3DRSP_IStaticCollider_SetRestitution(E3DRSP_IStaticCollider collider, float restitution);

	E3DRSP_FFI_EXPORT void E3DRSP_IStaticCollider_Destroy(E3DRSP_IStaticCollider collider);
#ifdef __cplusplus
}
#endif
