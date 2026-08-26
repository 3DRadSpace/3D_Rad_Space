#include "PostProcessEffect.h"
#include "../../../Graphics/Rendering/PostProcessEffect.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

E3DRSP_PostProcessEffect E3DRSP_PostProcessEffect_Create(E3DRSP_IGraphicsDevice device, const E3DRSP_ShaderDesc* desc)
{
	return new PostProcessEffect(static_cast<IGraphicsDevice*>(device), *reinterpret_cast<const ShaderDesc*>(desc));	
}

bool E3DRSP_PostProcessEffect_GetEnabled(E3DRSP_PostProcessEffect effect)
{
	return static_cast<PostProcessEffect*>(effect)->Enabled;
}

void E3DRSP_PostProcessEffect_SetEnabled(E3DRSP_PostProcessEffect effect, bool enabled)
{
	static_cast<PostProcessEffect*>(effect)->Enabled = enabled;
}

bool E3DRSP_PostProcessEffect_GetNotDepthAware(E3DRSP_PostProcessEffect effect)
{
	return static_cast<PostProcessEffect*>(effect)->NotDepthAware;
}
void E3DRSP_PostProcessEffect_SetNotDepthAware(E3DRSP_PostProcessEffect effect, bool notDepthAware)
{
	static_cast<PostProcessEffect*>(effect)->NotDepthAware = notDepthAware;
}

void E3DRSP_PostProcessEffect_Draw(E3DRSP_PostProcessEffect effect)
{
	static_cast<PostProcessEffect*>(effect)->Draw();
}

void E3DRSP_PostProcessEffect_Destroy(E3DRSP_PostProcessEffect effect)
{
	delete static_cast<PostProcessEffect*>(effect);
}