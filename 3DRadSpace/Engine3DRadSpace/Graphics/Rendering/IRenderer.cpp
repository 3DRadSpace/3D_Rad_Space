#include "IRenderer.hpp"
#include "../Effect.hpp"
#include "../../Core/IGame.hpp"
#include "RenderingManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

IRenderer::IRenderer(IGraphicsDevice* device, RenderingManager* owner) :
	_device(device),
	_owner(owner)
{
}

RenderPassType IRenderer::GetRenderPassType() const noexcept
{
	return RenderPassType::Opaque;
}

void IRenderer::Draw(ModelMeshPart* part, Effect* effect)
{
	this->_owner->Batcher.Draw(part, effect, GetRenderPassType());
}

RenderingManager* IRenderer::GetOwner() const noexcept
{
	return _owner;
}

IGraphicsDevice* IRenderer::GetGraphicsDevice() const noexcept
{
	return _device;
}