#pragma once
#include "ICollider.h"
#include "../Math/Vector3.h"

typedef void* E3DRSP_ICharacterController;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_ICharacterController_Move(E3DRSP_ICharacterController controller, const E3DRSP_Vector3* displacement);
	E3DRSP_FFI_EXPORT void E3DRSP_ICharacterController_Jump(E3DRSP_ICharacterController controller, float height);

	E3DRSP_FFI_EXPORT float E3DRSP_ICharacterController_GetHeight(E3DRSP_ICharacterController controller);
	E3DRSP_FFI_EXPORT void E3DRSP_ICharacterController_SetHeight(E3DRSP_ICharacterController controller, float height);

	E3DRSP_FFI_EXPORT float E3DRSP_ICharacterController_GetRadius(E3DRSP_ICharacterController controller);
	E3DRSP_FFI_EXPORT void E3DRSP_ICharacterController_SetRadius(E3DRSP_ICharacterController controller, float radius);

	E3DRSP_FFI_EXPORT void E3DRSP_ICharacterController_SetMaxSlopeAngle(E3DRSP_ICharacterController controller, float angle);
	E3DRSP_FFI_EXPORT float E3DRSP_ICharacterController_GetMaxSlopeAngle(E3DRSP_ICharacterController controller);

	E3DRSP_FFI_EXPORT void E3DRSP_ICharacterController_SetGravity(E3DRSP_ICharacterController controller, const E3DRSP_Vector3* gravity);
	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_ICharacterController_GetGravity(E3DRSP_ICharacterController controller);

	E3DRSP_FFI_EXPORT bool E3DRSP_ICharacterController_IsGrounded(E3DRSP_ICharacterController controller);

	E3DRSP_FFI_EXPORT void E3DRSP_ICharacterController_Destroy(E3DRSP_ICharacterController controller);
#ifdef __cplusplus
}
#endif
