#pragma once
#include "IRenderer.h"
#include "RenderingManager.h"
#include "../IDepthStencilBuffer.h"
#include "../ISamplerState.h"
#include "../../Math/Matrix4x4.h"
#include "../../Math/Vector2.h"

typedef void* E3DRSP_ShadowMapRenderer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_ShadowMapRenderer E3DRSP_ShadowMapRenderer_Create(E3DRSP_RenderingManager manager);

	E3DRSP_FFI_EXPORT float E3DRSP_ShadowMapRenderer_GetShadowMapSize(E3DRSP_ShadowMapRenderer renderer);
	E3DRSP_FFI_EXPORT void E3DRSP_ShadowMapRenderer_SetShadowMapSize(E3DRSP_ShadowMapRenderer renderer, float size);

	E3DRSP_FFI_EXPORT float E3DRSP_ShadowMapRenderer_GetDepthBias(E3DRSP_ShadowMapRenderer renderer);
	E3DRSP_FFI_EXPORT void E3DRSP_ShadowMapRenderer_SetDepthBias(E3DRSP_ShadowMapRenderer renderer, float depthBias);

	E3DRSP_FFI_EXPORT float E3DRSP_ShadowMapRenderer_GetSlopeScaleDepthBias(E3DRSP_ShadowMapRenderer renderer);
	E3DRSP_FFI_EXPORT void E3DRSP_ShadowMapRenderer_SetSlopeScaleDepthBias(E3DRSP_ShadowMapRenderer renderer, float slopeScaleDepthBias);

	E3DRSP_FFI_EXPORT float E3DRSP_ShadowMapRenderer_GetShadowIntensity(E3DRSP_ShadowMapRenderer renderer);
	E3DRSP_FFI_EXPORT void E3DRSP_ShadowMapRenderer_SetShadowIntensity(E3DRSP_ShadowMapRenderer renderer, float shadowIntensity);

	E3DRSP_FFI_EXPORT float E3DRSP_ShadowMapRenderer_GetNearPlane(E3DRSP_ShadowMapRenderer renderer);
	E3DRSP_FFI_EXPORT void E3DRSP_ShadowMapRenderer_SetNearPlane(E3DRSP_ShadowMapRenderer renderer, float nearPlane);

	E3DRSP_FFI_EXPORT float E3DRSP_ShadowMapRenderer_GetNormalOffsetScale(E3DRSP_ShadowMapRenderer renderer);
	E3DRSP_FFI_EXPORT void E3DRSP_ShadowMapRenderer_SetNormalOffsetScale(E3DRSP_ShadowMapRenderer renderer, float normalOffsetScale);

	E3DRSP_FFI_EXPORT E3DRSP_IDepthStencilBuffer E3DRSP_ShadowMapRenderer_GetShadowMap(E3DRSP_ShadowMapRenderer renderer);
	E3DRSP_FFI_EXPORT E3DRSP_ISamplerState E3DRSP_ShadowMapRenderer_GetSamplerState(E3DRSP_ShadowMapRenderer renderer);

	E3DRSP_FFI_EXPORT E3DRSP_Matrix4x4 E3DRSP_ShadowMapRenderer_GetLightViewMatrix(E3DRSP_ShadowMapRenderer renderer, const E3DRSP_Vector3* lightDir);
	E3DRSP_FFI_EXPORT E3DRSP_Matrix4x4 E3DRSP_ShadowMapRenderer_GetLightProjectionMatrix(E3DRSP_ShadowMapRenderer renderer);
#ifdef __cplusplus
}
#endif