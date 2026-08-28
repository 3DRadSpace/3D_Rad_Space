#pragma once
#include "ICamera.h"

typedef void* E3DRSP_CameraProvider;
typedef void* E3DRSP_IGame;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_CameraProvider E3DRSP_CameraProvider_Create(E3DRSP_IGame owner);
	E3DRSP_FFI_EXPORT E3DRSP_ICamera E3DRSP_CameraProvider_At(E3DRSP_CameraProvider provider, size_t index);
	E3DRSP_FFI_EXPORT E3DRSP_ICamera E3DRSP_CameraProvider_GetActiveCamera(E3DRSP_CameraProvider provider);
	E3DRSP_FFI_EXPORT void E3DRSP_CameraProvider_SetActiveCamera(E3DRSP_CameraProvider provider, E3DRSP_ICamera camera);
	E3DRSP_FFI_EXPORT void E3DRSP_CameraProvider_SetActiveCamera2(E3DRSP_CameraProvider provider, size_t indexCamera);
	E3DRSP_FFI_EXPORT void E3DRSP_CameraProvider_Refresh(E3DRSP_CameraProvider provider);
	E3DRSP_FFI_EXPORT size_t E3DRSP_CameraProvider_Count(E3DRSP_CameraProvider provider);
#ifdef __cplusplus
}
#endif