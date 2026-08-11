#include "TransparentForwardRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

TransparentForwardRenderer::TransparentForwardRenderer(RenderingManager* owner) :
	ForwardRenderer(owner)
{
}

bool TransparentForwardRenderer::IsRenderPassTypeSupported(RenderPassType passType) const noexcept
{
	switch (passType)
	{
	case RenderPassType::Transparent:
	case RenderPassType::TransparentNoShadow:
		return true;
	default:
		return false;
	}
}