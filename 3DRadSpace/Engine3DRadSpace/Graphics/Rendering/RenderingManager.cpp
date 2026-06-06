#include "RenderingManager.hpp"
#include "ForwardRenderer.hpp"
#include "ShadowMapRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

RenderingManager::RenderingManager(IGraphicsDevice* device) : 
	_device(device),
	Batcher(device)
{
	_renderers.emplace_back(std::make_unique<ForwardRenderer>(device));
	_renderers.emplace_back(std::make_unique<ShadowMapRenderer>(device));
}

void RenderingManager::Add(std::unique_ptr<IRenderer>&& renderPass)
{
	renderPass->SetOwner(_owner);
	_renderers.emplace_back(std::move(renderPass));
}

IRenderer* RenderingManager::operator[](size_t idx) const
{
	if (idx >= _renderers.size())
		throw std::out_of_range("Index out of range.");
	return _renderers[idx].get();
}

size_t RenderingManager::NumPasses() const noexcept
{
	return _renderers.size();
}

void RenderingManager::Remove(size_t idx)
{
	if (idx >= _renderers.size())
		throw std::out_of_range("Index out of range.");
	_renderers.erase(_renderers.begin() + idx);
}

void RenderingManager::Clear() noexcept
{
	_renderers.clear();
}