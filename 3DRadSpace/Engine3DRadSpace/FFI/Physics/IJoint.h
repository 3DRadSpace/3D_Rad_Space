#pragma once
#include "IDynamicCollider.h"
#include "JointType.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"

typedef void* E3DRSP_IJoint;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_JointType E3DRSP_IJoint_GetType(E3DRSP_IJoint joint);

	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetActors(E3DRSP_IJoint joint, E3DRSP_IDynamicCollider actor0, E3DRSP_IDynamicCollider actor1);

	E3DRSP_FFI_EXPORT E3DRSP_IDynamicCollider E3DRSP_IJoint_GetActor0(E3DRSP_IJoint joint);
	E3DRSP_FFI_EXPORT E3DRSP_IDynamicCollider E3DRSP_IJoint_GetActor1(E3DRSP_IJoint joint);

	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetLocalFrame0(E3DRSP_IJoint joint, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetLocalFrame1(E3DRSP_IJoint joint, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_IJoint_GetLocalFrame0Position(E3DRSP_IJoint joint);
	E3DRSP_FFI_EXPORT E3DRSP_Quaternion E3DRSP_IJoint_GetLocalFrame0Rotation(E3DRSP_IJoint joint);

	E3DRSP_FFI_EXPORT E3DRSP_Vector3 E3DRSP_IJoint_GetLocalFrame1Position(E3DRSP_IJoint joint);
	E3DRSP_FFI_EXPORT E3DRSP_Quaternion E3DRSP_IJoint_GetLocalFrame1Rotation(E3DRSP_IJoint joint);

	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetBreakForce(E3DRSP_IJoint joint, float force, float torque);
	E3DRSP_FFI_EXPORT float E3DRSP_IJoint_GetBreakForce(E3DRSP_IJoint joint);
	E3DRSP_FFI_EXPORT float E3DRSP_IJoint_GetBreakTorque(E3DRSP_IJoint joint);
	E3DRSP_FFI_EXPORT bool E3DRSP_IJoint_IsBroken(E3DRSP_IJoint joint);

	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_GetForce(E3DRSP_IJoint joint, E3DRSP_Vector3* linear, E3DRSP_Vector3* angular);

	// Joint type-specific parameters
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetDistanceLimit(E3DRSP_IJoint joint, float minDistance, float maxDistance);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetSphericalLimit(E3DRSP_IJoint joint, float yAngle, float zAngle);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetRevoluteLimit(E3DRSP_IJoint joint, float lower, float upper);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetRevoluteDrive(E3DRSP_IJoint joint, float velocity, float forceLimit, bool freespin);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetPrismaticLimit(E3DRSP_IJoint joint, float lower, float upper);

	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetD6Motion(E3DRSP_IJoint joint, int axis, int motionType);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetD6LinearLimit(E3DRSP_IJoint joint, float limit);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetD6TwistLimit(E3DRSP_IJoint joint, float lower, float upper);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetD6SwingLimit(E3DRSP_IJoint joint, float yAngle, float zAngle);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetD6Drive(E3DRSP_IJoint joint, int driveType, float stiffness, float damping, float forceLimit, bool acceleration);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetD6DrivePosition(E3DRSP_IJoint joint, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation);
	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_SetD6DriveVelocity(E3DRSP_IJoint joint, const E3DRSP_Vector3* linear, const E3DRSP_Vector3* angular);

	E3DRSP_FFI_EXPORT void E3DRSP_IJoint_Destroy(E3DRSP_IJoint joint);
#ifdef __cplusplus
}
#endif
