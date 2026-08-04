#pragma once
#include "../../Core/Libs.h"
#include "JointType.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Graphics/Model3D.h"

typedef void* E3DRSP_IPhysicsEngine;
typedef void* E3DRSP_IStaticCollider;
typedef void* E3DRSP_IDynamicCollider;
typedef void* E3DRSP_ICharacterController;
typedef void* E3DRSP_IJoint;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_IPhysicsEngine_Simulate(E3DRSP_IPhysicsEngine* physics, float dt);
	E3DRSP_FFI_EXPORT void* E3DRSP_IPhysicsEngine_GetScene(E3DRSP_IPhysicsEngine* physics);

	E3DRSP_FFI_EXPORT E3DRSP_IStaticCollider E3DRSP_IPhysicsEngine_CreateStaticCollider(
		E3DRSP_IPhysicsEngine* physics,
		E3DRSP_Model3D model,
		const E3DRSP_Vector3* position,
		const E3DRSP_Quaternion* rotation,
		const E3DRSP_Vector3* scale
	);

	E3DRSP_FFI_EXPORT E3DRSP_IDynamicCollider E3DRSP_IPhysicsEngine_CreateDynamicCollider(E3DRSP_IPhysicsEngine* physics);

	E3DRSP_FFI_EXPORT E3DRSP_ICharacterController E3DRSP_IPhysicsEngine_CreateCharacterController(
		E3DRSP_IPhysicsEngine* physics,
		float radius,
		float height,
		const E3DRSP_Vector3* position
	);

	E3DRSP_FFI_EXPORT E3DRSP_IJoint E3DRSP_IPhysicsEngine_CreateJoint(E3DRSP_IPhysicsEngine* physics, E3DRSP_JointType type);

	E3DRSP_FFI_EXPORT double E3DRSP_IPhysicsEngine_GetDT(E3DRSP_IPhysicsEngine* physics);

	E3DRSP_FFI_EXPORT void E3DRSP_IPhysicsEngine_SetGravity(E3DRSP_IPhysicsEngine* physics, const E3DRSP_Vector3* gravity);
	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_IPhysicsEngine_GetGravity(E3DRSP_IPhysicsEngine* physics);
#ifdef __cplusplus
}
#endif