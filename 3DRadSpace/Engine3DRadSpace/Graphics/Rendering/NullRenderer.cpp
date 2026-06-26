#include "NullRenderer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

NullRenderer::NullRenderer(IGraphicsDevice* device) : IRenderPass(device)
{
}

void NullRenderer::Begin()
{
}

void NullRenderer::End()
{
}