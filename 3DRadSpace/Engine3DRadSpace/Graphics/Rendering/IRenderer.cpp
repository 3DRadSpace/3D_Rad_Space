#include "IRenderer.hpp"
#include "../Effect.hpp"
#include "../../Core/IGame.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

IRenderer::IRenderer(IGraphicsDevice* device):
	_device(device)
{
}

void IRenderer::Draw(ModelMeshPart* part)
{
	part->Draw();
}

void IRenderer::Draw(IVertexBuffer* vertices, IIndexBuffer* indices, Effect* effect)
{
	effect->SetAll();
	_device->ImmediateContext()->DrawVertexBufferWithindices(vertices, indices);
}

IGraphicsDevice* IRenderer::GetDevice() const noexcept
{
	return _device;
}

void IRenderer::SetOwner(IGame* owner) noexcept
{
	_owner = owner;
}

IGame* IRenderer::GetOwner() const noexcept
{
	return _owner;
}