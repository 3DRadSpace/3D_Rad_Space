#include "IRenderer.hpp"
#include "../Effect.hpp"
#include "../../Core/IGame.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

IRenderer::IRenderer(RenderingManager* owner):
	_owner(owner)
{
}