#include "LinearPixelFogEffect.h"
#include "../../../Graphics/Rendering/LinearPixelFogEffect.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Math;

E3DRSP_LinearPixelFogEffect E3DRSP_LinearPixelFogEffect_Create(E3DRSP_IGraphicsDevice device)
{
	return new LinearPixelFogEffect(static_cast<IGraphicsDevice*>(device));
}

E3DRSP_Color E3DRSP_LinearPixelFogEffect_GetFogColor(E3DRSP_LinearPixelFogEffect effect)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<LinearPixelFogEffect*>(effect)->FogColor);
}

void E3DRSP_LinearPixelFogEffect_SetFogColor(E3DRSP_LinearPixelFogEffect effect, E3DRSP_Color color)
{
	static_cast<LinearPixelFogEffect*>(effect)->FogColor = std::bit_cast<Color>(color);
}

float E3DRSP_LinearPixelFogEffect_GetFogBegin(E3DRSP_LinearPixelFogEffect effect)
{
	return static_cast<LinearPixelFogEffect*>(effect)->FogBegin;
}

void E3DRSP_LinearPixelFogEffect_SetFogBegin(E3DRSP_LinearPixelFogEffect effect, float fogBegin)
{
	static_cast<LinearPixelFogEffect*>(effect)->FogBegin = fogBegin;
}

float E3DRSP_LinearPixelFogEffect_GetFogEnd(E3DRSP_LinearPixelFogEffect effect)
{
	return static_cast<LinearPixelFogEffect*>(effect)->FogEnd;
}

void E3DRSP_LinearPixelFogEffect_SetFogEnd(E3DRSP_LinearPixelFogEffect effect, float fogEnd)
{
	static_cast<LinearPixelFogEffect*>(effect)->FogEnd = fogEnd;
}

float E3DRSP_LinearPixelFogEffect_GetNearPlaneDistance(E3DRSP_LinearPixelFogEffect effect)
{
	return static_cast<LinearPixelFogEffect*>(effect)->NearPlaneDistance;
}

void E3DRSP_LinearPixelFogEffect_SetNearPlaneDistance(E3DRSP_LinearPixelFogEffect effect, float nearPlaneDistance)
{
	static_cast<LinearPixelFogEffect*>(effect)->NearPlaneDistance = nearPlaneDistance;
}

float E3DRSP_LinearPixelFogEffect_GetFarPlaneDistance(E3DRSP_LinearPixelFogEffect effect)
{
	return static_cast<LinearPixelFogEffect*>(effect)->FarPlaneDistance;
}

void E3DRSP_LinearPixelFogEffect_SetFarPlaneDistance(E3DRSP_LinearPixelFogEffect effect, float farPlaneDistance)
{
	static_cast<LinearPixelFogEffect*>(effect)->FarPlaneDistance = farPlaneDistance;
}