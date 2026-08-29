#include "ShadowMapRenderer.h"
#include "../../../Graphics/Rendering/ShadowMapRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

E3DRSP_ShadowMapRenderer E3DRSP_ShadowMapRenderer_Create(E3DRSP_RenderingManager manager)
{
	return new ShadowMapRenderer(static_cast<RenderingManager*>(manager));
}

float E3DRSP_ShadowMapRenderer_GetShadowMapSize(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->ShadowMapSize;
}

void E3DRSP_ShadowMapRenderer_SetShadowMapSize(E3DRSP_ShadowMapRenderer renderer, float size)
{
	static_cast<ShadowMapRenderer*>(renderer)->ShadowMapSize = size;
}

float E3DRSP_ShadowMapRenderer_GetDepthBias(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->ShadowBias;
}

void E3DRSP_ShadowMapRenderer_SetDepthBias(E3DRSP_ShadowMapRenderer renderer, float depthBias)
{
	static_cast<ShadowMapRenderer*>(renderer)->ShadowBias = depthBias;
}

float E3DRSP_ShadowMapRenderer_GetSlopeScaleDepthBias(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->ShadowSlopeBias;
}

void E3DRSP_ShadowMapRenderer_SetSlopeScaleDepthBias(E3DRSP_ShadowMapRenderer renderer, float slopeScaleDepthBias)
{
	static_cast<ShadowMapRenderer*>(renderer)->ShadowSlopeBias = slopeScaleDepthBias;
}

float E3DRSP_ShadowMapRenderer_GetShadowIntensity(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->ShadowIntensity;
}

void E3DRSP_ShadowMapRenderer_SetShadowIntensity(E3DRSP_ShadowMapRenderer renderer, float shadowIntensity)
{
	static_cast<ShadowMapRenderer*>(renderer)->ShadowIntensity = shadowIntensity;
}

float E3DRSP_ShadowMapRenderer_GetNearPlane(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->NearPlane;
}

void E3DRSP_ShadowMapRenderer_SetNearPlane(E3DRSP_ShadowMapRenderer renderer, float nearPlane)
{
	static_cast<ShadowMapRenderer*>(renderer)->NearPlane = nearPlane;
}

float E3DRSP_ShadowMapRenderer_GetNormalOffsetScale(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->NormalOffsetScale;
}

void E3DRSP_ShadowMapRenderer_SetNormalOffsetScale(E3DRSP_ShadowMapRenderer renderer, float normalOffsetScale)
{
	static_cast<ShadowMapRenderer*>(renderer)->NormalOffsetScale = normalOffsetScale;
}

E3DRSP_IDepthStencilBuffer E3DRSP_ShadowMapRenderer_GetShadowMap(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->GetShadowMap();
}
E3DRSP_ISamplerState E3DRSP_ShadowMapRenderer_GetSamplerState(E3DRSP_ShadowMapRenderer renderer)
{
	return static_cast<ShadowMapRenderer*>(renderer)->GetShadowSampler();
}

E3DRSP_Matrix4x4 E3DRSP_ShadowMapRenderer_GetLightViewMatrix(E3DRSP_ShadowMapRenderer renderer, const E3DRSP_Vector3* lightDir)
{
	return std::bit_cast<E3DRSP_Matrix4x4>(static_cast<ShadowMapRenderer*>(renderer)->ComputeLightViewMatrix(
	std::bit_cast<Math::Vector3>(*lightDir))
	);
}

E3DRSP_Matrix4x4 E3DRSP_ShadowMapRenderer_GetLightProjectionMatrix(E3DRSP_ShadowMapRenderer renderer)
{
	return std::bit_cast<E3DRSP_Matrix4x4>(static_cast<ShadowMapRenderer*>(renderer)->ComputeLightProjectionMatrix());
}