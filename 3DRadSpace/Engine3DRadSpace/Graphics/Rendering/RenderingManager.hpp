#pragma once
#include "IRenderer.hpp"
#include "../../Core/IService.hpp"
#include "../IGraphicsDevice.hpp"
#include "MeshBatcher.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	///	Holds the rendering passes.
	/// </summary>
	class RenderingManager : public IService
	{
		IGraphicsDevice* _device;

		std::vector<std::unique_ptr<IRenderer>> _renderers;
	public:
		RenderingManager(IGraphicsDevice* device);

		MeshBatcher Batcher;

		template<typename R, typename... Args>
		void Add(Args&&... args)
		{
			auto renderer = std::make_unique<R>(_device, std::forward<Args>(args)...);
			renderer->SetOwner(_owner);
			_renderers.push_back(std::move(renderer));
		}

		void Add(std::unique_ptr<IRenderer>&& renderPass);
		IRenderer* operator[](size_t idx) const;
		size_t NumPasses() const noexcept;
		void Remove(size_t idx);
		void Clear() noexcept;

		~RenderingManager() override = default;
	};
}