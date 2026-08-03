#include "ICharacterController.h"
#include "../../Physics/ICharacterController.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

void E3DRSP_ICharacterController_Move(E3DRSP_ICharacterController controller, const E3DRSP_Vector3* displacement)
{
	if (controller == nullptr || displacement == nullptr) return;
	static_cast<ICharacterController*>(controller)->Move(Vector3(displacement->X, displacement->Y, displacement->Z));
}

void E3DRSP_ICharacterController_Jump(E3DRSP_ICharacterController controller, float height)
{
	if (controller == nullptr) return;
	static_cast<ICharacterController*>(controller)->Jump(height);
}

float E3DRSP_ICharacterController_GetHeight(E3DRSP_ICharacterController controller)
{
	if (controller == nullptr) return 0.0f;
	return static_cast<ICharacterController*>(controller)->GetHeight();
}

void E3DRSP_ICharacterController_SetHeight(E3DRSP_ICharacterController controller, float height)
{
	if (controller == nullptr) return;
	static_cast<ICharacterController*>(controller)->SetHeight(height);
}

float E3DRSP_ICharacterController_GetRadius(E3DRSP_ICharacterController controller)
{
	if (controller == nullptr) return 0.0f;
	return static_cast<ICharacterController*>(controller)->GetRadius();
}

void E3DRSP_ICharacterController_SetRadius(E3DRSP_ICharacterController controller, float radius)
{
	if (controller == nullptr) return;
	static_cast<ICharacterController*>(controller)->SetRadius(radius);
}

void E3DRSP_ICharacterController_SetMaxSlopeAngle(E3DRSP_ICharacterController controller, float angle)
{
	if (controller == nullptr) return;
	static_cast<ICharacterController*>(controller)->SetMaxSlopeAngle(angle);
}

float E3DRSP_ICharacterController_GetMaxSlopeAngle(E3DRSP_ICharacterController controller)
{
	if (controller == nullptr) return 0.0f;
	return static_cast<ICharacterController*>(controller)->GetMaxSlopeAngle();
}

void E3DRSP_ICharacterController_SetGravity(E3DRSP_ICharacterController controller, const E3DRSP_Vector3* gravity)
{
	if (controller == nullptr || gravity == nullptr) return;
	static_cast<ICharacterController*>(controller)->SetGravity(Vector3(gravity->X, gravity->Y, gravity->Z));
}

E3DRSP_Vector3 E3DRSP_ICharacterController_GetGravity(E3DRSP_ICharacterController controller)
{
	if (controller == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto gravity = static_cast<ICharacterController*>(controller)->GetGravity();
	return E3DRSP_Vector3{ gravity.X, gravity.Y, gravity.Z };
}

bool E3DRSP_ICharacterController_IsGrounded(E3DRSP_ICharacterController controller)
{
	if (controller == nullptr) return false;
	return static_cast<ICharacterController*>(controller)->IsGrounded();
}

void E3DRSP_ICharacterController_Destroy(E3DRSP_ICharacterController controller)
{
	if (controller == nullptr) return;
	delete static_cast<ICharacterController*>(controller);
}
