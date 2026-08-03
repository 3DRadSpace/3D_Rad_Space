#include "IJoint.h"
#include "../../Physics/IJoint.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

E3DRSP_JointType E3DRSP_IJoint_GetType(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return E3DRSP_JointType_Fixed;
	return static_cast<E3DRSP_JointType>(static_cast<IJoint*>(joint)->GetType());
}

void E3DRSP_IJoint_SetActors(E3DRSP_IJoint joint, E3DRSP_IDynamicCollider actor0, E3DRSP_IDynamicCollider actor1)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetActors(
		static_cast<IDynamicCollider*>(actor0),
		static_cast<IDynamicCollider*>(actor1)
	);
}

E3DRSP_IDynamicCollider E3DRSP_IJoint_GetActor0(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return nullptr;
	return static_cast<IJoint*>(joint)->GetActor0();
}

E3DRSP_IDynamicCollider E3DRSP_IJoint_GetActor1(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return nullptr;
	return static_cast<IJoint*>(joint)->GetActor1();
}

void E3DRSP_IJoint_SetLocalFrame0(E3DRSP_IJoint joint, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation)
{
	if (joint == nullptr || position == nullptr || rotation == nullptr) return;
	static_cast<IJoint*>(joint)->SetLocalFrame0(
		Vector3(position->X, position->Y, position->Z),
		Quaternion(rotation->X, rotation->Y, rotation->Z, rotation->W)
	);
}

void E3DRSP_IJoint_SetLocalFrame1(E3DRSP_IJoint joint, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation)
{
	if (joint == nullptr || position == nullptr || rotation == nullptr) return;
	static_cast<IJoint*>(joint)->SetLocalFrame1(
		Vector3(position->X, position->Y, position->Z),
		Quaternion(rotation->X, rotation->Y, rotation->Z, rotation->W)
	);
}

E3DRSP_Vector3 E3DRSP_IJoint_GetLocalFrame0Position(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto pos = static_cast<IJoint*>(joint)->GetLocalFrame0Position();
	return E3DRSP_Vector3{ pos.X, pos.Y, pos.Z };
}

E3DRSP_Quaternion E3DRSP_IJoint_GetLocalFrame0Rotation(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return E3DRSP_Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
	auto rot = static_cast<IJoint*>(joint)->GetLocalFrame0Rotation();
	return E3DRSP_Quaternion{ rot.X, rot.Y, rot.Z, rot.W };
}

E3DRSP_Vector3 E3DRSP_IJoint_GetLocalFrame1Position(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto pos = static_cast<IJoint*>(joint)->GetLocalFrame1Position();
	return E3DRSP_Vector3{ pos.X, pos.Y, pos.Z };
}

E3DRSP_Quaternion E3DRSP_IJoint_GetLocalFrame1Rotation(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return E3DRSP_Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
	auto rot = static_cast<IJoint*>(joint)->GetLocalFrame1Rotation();
	return E3DRSP_Quaternion{ rot.X, rot.Y, rot.Z, rot.W };
}

void E3DRSP_IJoint_SetBreakForce(E3DRSP_IJoint joint, float force, float torque)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetBreakForce(force, torque);
}

float E3DRSP_IJoint_GetBreakForce(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return 0.0f;
	return static_cast<IJoint*>(joint)->GetBreakForce();
}

float E3DRSP_IJoint_GetBreakTorque(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return 0.0f;
	return static_cast<IJoint*>(joint)->GetBreakTorque();
}

bool E3DRSP_IJoint_IsBroken(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return false;
	return static_cast<IJoint*>(joint)->IsBroken();
}

void E3DRSP_IJoint_GetForce(E3DRSP_IJoint joint, E3DRSP_Vector3* linear, E3DRSP_Vector3* angular)
{
	if (joint == nullptr || linear == nullptr || angular == nullptr) return;
	Vector3 linearForce, angularForce;
	static_cast<IJoint*>(joint)->GetForce(linearForce, angularForce);
	linear->X = linearForce.X;
	linear->Y = linearForce.Y;
	linear->Z = linearForce.Z;
	angular->X = angularForce.X;
	angular->Y = angularForce.Y;
	angular->Z = angularForce.Z;
}

void E3DRSP_IJoint_SetDistanceLimit(E3DRSP_IJoint joint, float minDistance, float maxDistance)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetDistanceLimit(minDistance, maxDistance);
}

void E3DRSP_IJoint_SetSphericalLimit(E3DRSP_IJoint joint, float yAngle, float zAngle)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetSphericalLimit(yAngle, zAngle);
}

void E3DRSP_IJoint_SetRevoluteLimit(E3DRSP_IJoint joint, float lower, float upper)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetRevoluteLimit(lower, upper);
}

void E3DRSP_IJoint_SetRevoluteDrive(E3DRSP_IJoint joint, float velocity, float forceLimit, bool freespin)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetRevoluteDrive(velocity, forceLimit, freespin);
}

void E3DRSP_IJoint_SetPrismaticLimit(E3DRSP_IJoint joint, float lower, float upper)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetPrismaticLimit(lower, upper);
}

void E3DRSP_IJoint_SetD6Motion(E3DRSP_IJoint joint, int axis, int motionType)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetD6Motion(axis, motionType);
}

void E3DRSP_IJoint_SetD6LinearLimit(E3DRSP_IJoint joint, float limit)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetD6LinearLimit(limit);
}

void E3DRSP_IJoint_SetD6TwistLimit(E3DRSP_IJoint joint, float lower, float upper)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetD6TwistLimit(lower, upper);
}

void E3DRSP_IJoint_SetD6SwingLimit(E3DRSP_IJoint joint, float yAngle, float zAngle)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetD6SwingLimit(yAngle, zAngle);
}

void E3DRSP_IJoint_SetD6Drive(E3DRSP_IJoint joint, int driveType, float stiffness, float damping, float forceLimit, bool acceleration)
{
	if (joint == nullptr) return;
	static_cast<IJoint*>(joint)->SetD6Drive(driveType, stiffness, damping, forceLimit, acceleration);
}

void E3DRSP_IJoint_SetD6DrivePosition(E3DRSP_IJoint joint, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation)
{
	if (joint == nullptr || position == nullptr || rotation == nullptr) return;
	static_cast<IJoint*>(joint)->SetD6DrivePosition(
		Vector3(position->X, position->Y, position->Z),
		Quaternion(rotation->X, rotation->Y, rotation->Z, rotation->W)
	);
}

void E3DRSP_IJoint_SetD6DriveVelocity(E3DRSP_IJoint joint, const E3DRSP_Vector3* linear, const E3DRSP_Vector3* angular)
{
	if (joint == nullptr || linear == nullptr || angular == nullptr) return;
	static_cast<IJoint*>(joint)->SetD6DriveVelocity(
		Vector3(linear->X, linear->Y, linear->Z),
		Vector3(angular->X, angular->Y, angular->Z)
	);
}

void E3DRSP_IJoint_Destroy(E3DRSP_IJoint joint)
{
	if (joint == nullptr) return;
	delete static_cast<IJoint*>(joint);
}
