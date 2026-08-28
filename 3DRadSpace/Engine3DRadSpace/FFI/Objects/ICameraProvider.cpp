#include "CameraProvider.h"
#include "../../Objects/CameraProvider.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

E3DRSP_CameraProvider E3DRSP_CameraProvider_Create(E3DRSP_IGame owner)
{
	return new CameraProvider(static_cast<IGame*>(owner));
}

E3DRSP_ICamera E3DRSP_CameraProvider_At(E3DRSP_CameraProvider provider, size_t index)
{
	return static_cast<CameraProvider*>(provider)->operator[](index);
}

E3DRSP_ICamera E3DRSP_CameraProvider_GetActiveCamera(E3DRSP_CameraProvider provider)
{
	return static_cast<CameraProvider*>(provider)->GetActiveCamera();
}

void E3DRSP_CameraProvider_SetActiveCamera(E3DRSP_CameraProvider provider, E3DRSP_ICamera camera)
{
	static_cast<CameraProvider*>(provider)->SetActiveCamera(static_cast<ICamera*>(camera));
}

void E3DRSP_CameraProvider_SetActiveCamera2(E3DRSP_CameraProvider provider, size_t indexCamera)
{
	static_cast<CameraProvider*>(provider)->SetActiveCamera(indexCamera);
}

void E3DRSP_CameraProvider_Refresh(E3DRSP_CameraProvider provider)
{
	static_cast<CameraProvider*>(provider)->Refresh();
}

size_t E3DRSP_CameraProvider_Count(E3DRSP_CameraProvider provider)
{
	return static_cast<CameraProvider*>(provider)->Count();
}