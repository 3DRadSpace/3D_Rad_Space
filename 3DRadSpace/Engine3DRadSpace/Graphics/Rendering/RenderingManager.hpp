#pragma once
#include "IRenderer.hpp"
#include "../../Core/IService.hpp"
#include "../IGraphicsDevice.hpp"

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
		
		template<typename R, typename... Args>
		void Add(Args&&... args)
		{
			_renderers.push_back(std::make_unique<R>(_device, std::forward<Args>(args)...));
		}

		void Add(std::unique_ptr<IRenderer>&& renderPass);
		IRenderer* operator[](size_t idx) const;
		size_t NumPasses() const noexcept;
		void Remove(size_t idx);
		void Clear() noexcept;

		~RenderingManager() override = default;
	};
}