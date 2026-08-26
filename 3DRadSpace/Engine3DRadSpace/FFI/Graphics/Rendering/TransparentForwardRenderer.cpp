#include "TransparentForwardRenderer.h"
#include "../../../Graphics/Rendering/TransparentForwardRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

E3DRSP_TransparentForwardRenderer E3DRSP_TransparentForwardRenderer_Create(E3DRSP_RenderingManager manager)
{
	return new E3DRSP_TransparentForwardRenderer(static_cast<RenderingManager*>(manager));
}