#include "IRenderer.h"
#include "../../../Graphics/Rendering/IRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

void E3DRSP_IRenderer_Begin(E3DRSP_IRenderer renderer)
{
	static_cast<IRenderer*>(renderer)->Begin();
}

void E3DRSP_IRenderer_Draw(E3DRSP_IRenderer renderer, const E3DRSP_MeshPartDrawInfo* part)
{
	static_cast<IRenderer*>(renderer)->Draw(std::bit_cast<const MeshPartDrawInfo>(*part));
}

void E3DRSP_IRenderer_End(E3DRSP_IRenderer renderer)
{
	static_cast<IRenderer*>(renderer)->End();
}

bool E3DRSP_IRenderer_IsRenderPassTypeSupported(const E3DRSP_IRenderer renderer, E3DRSP_RenderPassType passType)
{
	return static_cast<const IRenderer*>(renderer)->IsRenderPassTypeSupported(static_cast<RenderPassType>(passType));
}

void E3DRSP_IRenderer_Destroy(E3DRSP_IRenderer renderer)
{
	delete static_cast<IRenderer*>(renderer);
}