#include "IRenderer.hpp"
#include "../Effect.hpp"
#include "../../Core/IGame.hpp"
#include "RenderingManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

IRenderer::IRenderer(RenderingManager* owner):
	_device(owner->GetDevice()),
	_context(owner->GetDevice()->ImmediateContext()),
	_owner(owner)
{
}