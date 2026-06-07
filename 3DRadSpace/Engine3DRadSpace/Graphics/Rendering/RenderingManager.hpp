#pragma once
#include "IRenderer.hpp"
#include "../../Core/IService.hpp"
#include "../IGraphicsDevice.hpp"
#include "MeshBatcher.hpp"
#include "DirectionalLight.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Provides support for advanced rendering techniques, such as mech batching and drawing passes.
	/// </summary>
	class RenderingManager : public IService
	{
		IGraphicsDevice* _device;

		std::vector<std::unique_ptr<IRenderer>> _renderers;
	public:
		/// <summary>
		/// Creates an RenderingManager with classical forward rendering and shadow mapping passes.
		/// </summary>
		///	<param name="device">Graphics device to use for rendering.</param>
		RenderingManager(IGraphicsDevice* device);

		MeshBatcher Batcher;

		/// <summary>
		/// Emplaces a new renderer of type R with the given arguments.
		/// </summary>
		/// <typeparam name="R">Renderer type</typeparam>
		/// <typeparam name="...Args">Renderer construction arguments</typeparam>
		/// <param name="...args">Arguments to construct the renderer</param>
		template<typename R, typename... Args>
		void Add(Args&&... args)
		{
			auto renderer = std::make_unique<R>(_device, std::forward<Args>(args)...);
			renderer->SetOwner(this);
			_renderers.push_back(std::move(renderer));
		}

		/// <summary>
		/// Transfers ownership of the given renderer named "renderPass" to this instance.
		/// </summary>
		/// <param name="renderPass">RenderPass to have ownership transferred.</param>
		void Add(std::unique_ptr<IRenderer>&& renderPass);
		/// <summary>
		/// Gets the idx-th IRenderer instance owned by this instance.
		/// If idx is out of range, an std::out_of_range exception is thrown.
		/// </summary>
		/// <param name="idx">Index of the IRenderer class</param>
		/// <returns>idx-th IRenderer instance.</returns>
		IRenderer* operator[](size_t idx) const;
		/// <summary>
		/// Returns the number of IRenderer instances owned by this RenderingManager instance.
		/// </summary>
		/// <returns>Number of IRenderer instances.</returns>
		size_t NumPasses() const noexcept;
		/// <summary>
		/// Removes the idx-th IRenderer instance.
		/// </summary>
		/// <param name="idx">Index</param>
		void Remove(size_t idx);
		/// <summary>
		/// Clears the internal list of render passes.
		/// </summary>
		void Clear() noexcept;

		/// <summary>
		/// A directional light used for the main light source in the scene. This is used for forward rendering and shadow mapping.
		/// </summary>
		DirectionalLight MainLight;

		void Prepare();
		void Draw();

		~RenderingManager() override = default;
	};
}