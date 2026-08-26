#include "NullRenderer.h"
#include "../../../Graphics/Rendering/NullRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

E3DRSP_NullRenderer E3DRSP_NullRenderer_Create(E3DRSP_RenderingManager manager)
{
	return new NullRenderer(static_cast<RenderingManager*>(manager));
}