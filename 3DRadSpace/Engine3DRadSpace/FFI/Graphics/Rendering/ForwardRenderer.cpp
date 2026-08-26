#include "ForwardRenderer.h"
#include "../../../Graphics/Rendering/ForwardRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

E3DRSP_ForwardRenderer E3DRSP_ForwardRenderer_Create(E3DRSP_RenderingManager manager)
{
	return new ForwardRenderer(static_cast<RenderingManager*>(manager));
}