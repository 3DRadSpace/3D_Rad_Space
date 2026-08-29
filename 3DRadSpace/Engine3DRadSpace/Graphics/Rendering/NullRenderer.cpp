#include "NullRenderer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

NullRenderer::NullRenderer(RenderingManager* owner) : IRenderer(owner)
{
}

void NullRenderer::Begin()
{
}

void NullRenderer::Draw(const MeshPartDrawInfo& part)
{
	(void)part;
}

void NullRenderer::End()
{
}

bool NullRenderer::IsRenderPassTypeSupported(RenderPassType passType) const noexcept
{
	return true;
}