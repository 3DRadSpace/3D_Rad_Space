#pragma once
#include "../IShader.h"
#include "../ShaderDesc.h"

typedef void* E3DRSP_PostProcessEffect;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_PostProcessEffect E3DRSP_PostProcessEffect_Create(E3DRSP_IGraphicsDevice device, const E3DRSP_ShaderDesc* desc);

	E3DRSP_FFI_EXPORT bool E3DRSP_PostProcessEffect_GetEnabled(E3DRSP_PostProcessEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessEffect_SetEnabled(E3DRSP_PostProcessEffect effect, bool enabled);

	E3DRSP_FFI_EXPORT bool E3DRSP_PostProcessEffect_GetNotDepthAware(E3DRSP_PostProcessEffect effect);
	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessEffect_SetNotDepthAware(E3DRSP_PostProcessEffect effect, bool notDepthAware);

	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessEffect_Draw(E3DRSP_PostProcessEffect effect);

	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessEffect_Destroy(E3DRSP_PostProcessEffect effect);
#ifdef __cplusplus
}
#endif