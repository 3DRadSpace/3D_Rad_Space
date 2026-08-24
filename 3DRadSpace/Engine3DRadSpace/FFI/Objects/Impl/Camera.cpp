#include "Camera.h"
#include "../../../Objects/Impl/Camera.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_Camera E3DRSP_Camera_Create()
{
	return new Camera();
}

E3DRSP_Vector3 E3DRSP_Camera_GetNormal(E3DRSP_Camera camera)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<Camera*>(camera)->Normal);
}
void E3DRSP_Camera_SetNormal(E3DRSP_Camera camera, const E3DRSP_Vector3* vector)
{
	static_cast<Camera*>(camera)->Normal = Vector3{vector->X, vector->Y, vector->Z};
}

float E3DRSP_Camera_GetAspectRatio(E3DRSP_Camera camera)
{
	return static_cast<Camera*>(camera)->AspectRatio;
}

void E3DRSP_Camera_SetAspectRatio(E3DRSP_Camera camera, float aspectRatio)
{
	static_cast<Camera*>(camera)->AspectRatio = aspectRatio;
}

float E3DRSP_Camera_GetFOV(E3DRSP_Camera camera)
{
	return static_cast<Camera*>(camera)->FieldOfView;
}

void E3DRSP_Camera_SetFOV(E3DRSP_Camera camera, float fov)
{
	static_cast<Camera*>(camera)->FieldOfView = fov;
}

float E3DRSP_Camera_GetNPD(E3DRSP_Camera camera)
{
	return static_cast<Camera*>(camera)->NearPlaneDistance;
}

void E3DRSP_Camera_SetNPD(E3DRSP_Camera camera, float nearPlaneDistance)
{
	static_cast<Camera*>(camera)->NearPlaneDistance = nearPlaneDistance;
}

float E3DRSP_Camera_GetFPD(E3DRSP_Camera camera)
{
	return static_cast<Camera*>(camera)->FarPlaneDistance;
}

void E3DRSP_Camera_SetFPD(E3DRSP_Camera camera, float farPlaneDistance)
{
	static_cast<Camera*>(camera)->FarPlaneDistance = farPlaneDistance;
}

void E3DRSP_Camera_SetLookAt(E3DRSP_Camera camera, const E3DRSP_Vector3* vector)
{
	static_cast<Camera*>(camera)->SetLookAt(std::bit_cast<Vector3>(*vector));
}