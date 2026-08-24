#include "RenderingManager.hpp"
#include "ForwardRenderer.hpp"
#include "ShadowMapRenderer.hpp"
#include "NullRenderer.hpp"
#include "../Model3D.hpp"
#include "TransparentForwardRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

RenderingManager::RenderingManager(IGraphicsDevice* device) : IService(device->GetOwner()),
	_device(device),
	MainLight()
{
}

RenderingManager::RenderingManager(RenderingManager&& other) noexcept :
	IService(std::move(other)),
	_device(other._device),
	_renderers(std::move(other._renderers)),
	_meshParts(std::move(other._meshParts)),
	MainLight(std::move(other.MainLight))
{
	for (auto& renderer : _renderers)
	{
		renderer->_owner = this;
	}

	other._device = nullptr;
}

RenderingManager& RenderingManager::operator=(RenderingManager&& other) noexcept
{
	if (this != &other)
	{
		IService::operator=(std::move(other));

		_device = other._device;
		_renderers = std::move(other._renderers);
		_meshParts = std::move(other._meshParts);
		MainLight = std::move(other.MainLight);
		for (auto& renderer : _renderers)
		{
			renderer->_owner = this;
		}
		other._device = nullptr;
	}
	return *this;
}

void RenderingManager::Add(std::unique_ptr<IRenderer>&& renderPass)
{
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

void RenderingManager::Execute()
{
	for (auto& renderer : _renderers)
	{
		renderer->Begin();

		for (auto& part : _meshParts)
		{
			if (renderer->IsRenderPassTypeSupported(part.PassType))
				renderer->Draw(part.Part, &part.Part->Material);
		}

		renderer->End();
	}

	_meshParts.clear();
}

void RenderingManager::Draw(Model3D* model, RenderPassType passType)
{
	if (model == nullptr) return;

	for (auto &mesh : (*model))
	{
		for (auto& part : (*mesh))
		{
			Draw(part.get(), passType);
		}
	}
}

void RenderingManager::Draw(ModelMeshPart* part, RenderPassType passType)
{
	if (part == nullptr) return;
	part->Material.HasShadows = (passType == RenderPassType::Opaque || passType == RenderPassType::Transparent);
	_meshParts.push_back({ part, passType });
}

std::unique_ptr<RenderingManager> RenderingManager::CreateForward(IGraphicsDevice* device)
{
	RenderingManager manager(device);
	manager.Add<ShadowMapRenderer>();
	manager.Add<ForwardRenderer>();
	manager.Add<TransparentForwardRenderer>();
	return std::make_unique<RenderingManager>(std::move(manager));
}

std::unique_ptr<RenderingManager> RenderingManager::CreateTrivial(IGraphicsDevice* device)
{
	RenderingManager manager(device);
	manager.Add<ForwardRenderer>();
	return std::make_unique<RenderingManager>(std::move(manager));
}

std::unique_ptr<RenderingManager> RenderingManager::CreateNull(IGraphicsDevice* device)
{
	RenderingManager manager(device);
	manager.Add<NullRenderer>();
	return std::make_unique<RenderingManager>(std::move(manager));
}

IGraphicsDevice* RenderingManager::GetDevice() const noexcept
{
	return _device;
}

RenderingManager::~RenderingManager()
{
	//for (auto& renderer : _renderers)
	//{
	//	renderer->_owner = nullptr;
	//}
}