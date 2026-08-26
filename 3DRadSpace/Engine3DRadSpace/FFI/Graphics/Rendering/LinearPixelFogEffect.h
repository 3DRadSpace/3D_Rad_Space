#pragma once
#include "PostProcessEffect.h"
#include "../../Math/Color.h"

typedef void* E3DRSP_LinearPixelFogEffect;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT  E3DRSP_LinearPixelFogEffect E3DRSP_LinearPixelFogEffect_Create(E3DRSP_IGraphicsDevice device);

	E3DRSP_FFI_EXPORT E3DRSP_Color E3DRSP_LinearPixelFogEffect_GetFogColor(E3DRSP_LinearPixelFogEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_LinearPixelFogEffect_SetFogColor(E3DRSP_LinearPixelFogEffect effect, E3DRSP_Color color);

	E3DRSP_FFI_EXPORT float E3DRSP_LinearPixelFogEffect_GetFogBegin(E3DRSP_LinearPixelFogEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_LinearPixelFogEffect_SetFogBegin(E3DRSP_LinearPixelFogEffect effect, float fogBegin);

	E3DRSP_FFI_EXPORT float E3DRSP_LinearPixelFogEffect_GetFogEnd(E3DRSP_LinearPixelFogEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_LinearPixelFogEffect_SetFogEnd(E3DRSP_LinearPixelFogEffect effect, float fogEnd);

	E3DRSP_FFI_EXPORT float E3DRSP_LinearPixelFogEffect_GetFogBegin(E3DRSP_LinearPixelFogEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_LinearPixelFogEffect_SetFogBegin(E3DRSP_LinearPixelFogEffect effect, float fogBegin);

	E3DRSP_FFI_EXPORT float E3DRSP_LinearPixelFogEffect_GetFogEnd(E3DRSP_LinearPixelFogEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_LinearPixelFogEffect_SetFogEnd(E3DRSP_LinearPixelFogEffect effect, float fogEnd);

	E3DRSP_FFI_EXPORT float E3DRSP_LinearPixelFogEffect_GetNearPlaneDistance(E3DRSP_LinearPixelFogEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_LinearPixelFogEffect_SetNearPlaneDistance(E3DRSP_LinearPixelFogEffect effect, float nearPlaneDistance);

	E3DRSP_FFI_EXPORT float E3DRSP_LinearPixelFogEffect_GetFarPlaneDistance(E3DRSP_LinearPixelFogEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_LinearPixelFogEffect_SetFarPlaneDistance(E3DRSP_LinearPixelFogEffect effect, float farPlaneDistance);
#ifdef __cplusplus
}
#endif