#pragma once
#include "../ModelMeshPart.hpp"
#include "RenderPassType.hpp"
#include "DrawCall.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Manages lists of draw calls. Doesn't render anything by itself.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT MeshBatcher
	{
		IGraphicsDevice* _device;

		std::vector<DrawCall> _drawCalls;
	public:
		MeshBatcher(IGraphicsDevice* device);

		MeshBatcher(const MeshBatcher&) = delete;
		MeshBatcher& operator=(const MeshBatcher&) = delete;

		MeshBatcher(MeshBatcher&&) noexcept = default;
		MeshBatcher& operator=(MeshBatcher&&) noexcept = default;

		/// <summary>
		/// Clears the draw call list.
		/// </summary>
		void Clear();
		/// <summary>
		/// Submits an mesh part this draw call list.
		/// </summary>
		/// <param name="meshPart"></param>
		void Submit(ModelMeshPart* meshPart, RenderPassType passType = RenderPassType::Opaque, std::vector<std::unique_ptr<std::byte[]>>&& instanceData = {});
		
		/// <summary>
		/// Returns the list of draw calls and the count.
		/// </summary>
		/// <returns></returns>
		std::pair<DrawCall*, size_t> GetDrawCalls();

		/// <summary>
		/// Returns draw calls filtered by render pass type.
		/// </summary>
		/// <param name="filter">The render pass type to filter by.</param>
		/// <returns>A vector containing pointers to the draw calls that match the filter.</returns>
		std::vector<DrawCall*> GetDrawCalls(RenderPassType filter);
	};
}