#pragma once
#include "IRenderer.hpp"
#include "../../Core/IService.hpp"
#include "../IGraphicsDevice.hpp"
#include "RenderPassType.hpp"
#include "DirectionalLight.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Provides support for advanced rendering techniques, such as mech batching and drawing passes.
	/// </summary>
	class RenderingManager : public IService
	{
		struct MeshPartDrawInfo
		{
			ModelMeshPart* Part;
			RenderPassType PassType;
		};

		IGraphicsDevice* _device;

		std::vector<std::unique_ptr<IRenderer>> _renderers;
		std::vector<MeshPartDrawInfo> _meshParts;

		RenderingManager(IGraphicsDevice* device, std::nullptr_t dummy);
	public:
		/// <summary>
		/// Creates an RenderingManager with classical forward rendering and shadow mapping passes.
		/// </summary>
		///	<param name="device">Graphics device to use for rendering.</param>
		RenderingManager(IGraphicsDevice* device);

		RenderingManager(RenderingManager&&) noexcept;
		RenderingManager& operator=(RenderingManager&&) noexcept;

		/// <summary>
		/// Emplaces a new renderer of type R with the given arguments.
		/// </summary>
		/// <typeparam name="R">Renderer type</typeparam>
		/// <typeparam name="...Args">Renderer construction arguments</typeparam>
		/// <param name="...args">Arguments to construct the renderer</param>
		template<typename R, typename... Args>
		void Add(Args&&... args)
		{
			_renderers.emplace_back(std::make_unique<R>(this, std::forward<Args>(args)...));
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

		void Draw(Model3D* model, RenderPassType passType = RenderPassType::Opaque);
		void Draw(ModelMeshPart* part, RenderPassType passType = RenderPassType::Opaque);

		/// <summary>
		/// Executes all render passes in order, drawing all submitted meshes.
		/// </summary>
		void Execute();

		static std::unique_ptr<RenderingManager> CreateForward(IGraphicsDevice* device);
		static std::unique_ptr<RenderingManager> CreateNull(IGraphicsDevice* device);

		DirectionalLight MainLight;

		/// <summary>
		///	Returns the idx-th renderer of type T, or nullptr if not found.
		/// </summary>
		/// <typeparam name="T">Type of the renderer to retrieve.</typeparam>
		/// <param name="idx">Index of the renderer of type T to retrieve.</param>
		/// <returns>Pointer to the idx-th renderer of type T, or nullptr if not found.</returns>
		template<typename T>
		T* Get(size_t idx = 0)
		{
			size_t count = 0;
			for (auto& renderer : _renderers)
			{
				if (dynamic_cast<T*>(renderer.get()) != nullptr)
				{
					if (count == idx)
						return static_cast<T*>(renderer.get());
					count++;
				}
			}
			return nullptr;
		}

		IGraphicsDevice* GetDevice() const noexcept;

		~RenderingManager() override = default;
	};
}