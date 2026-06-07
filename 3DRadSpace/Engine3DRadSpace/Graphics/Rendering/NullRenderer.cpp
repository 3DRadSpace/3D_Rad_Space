#include "NullRenderer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

NullRenderer::NullRenderer(IGraphicsDevice* device, RenderingManager* owner) : IRenderer(device, owner)
{
}

void NullRenderer::Begin()
{
}

void NullRenderer::End()
{
}