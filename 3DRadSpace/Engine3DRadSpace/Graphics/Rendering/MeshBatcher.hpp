#pragma once
#include "../ModelMeshPart.hpp"
#include "RenderPassType.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Manages batching meshes using plain or instanced drawing calls.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT MeshBatcher
	{
		IGraphicsDevice* _device;

		struct DrawCall
		{
			ModelMeshPart* MeshPart;
			std::vector<Math::Matrix4x4> Transforms;
			std::vector<std::unique_ptr<std::byte[]>> InstanceData;
			RenderPassType PassType;

			DrawCall() = default;
			DrawCall(DrawCall&&) noexcept = default;
			DrawCall& operator=(DrawCall&&) noexcept = default;

			DrawCall(const DrawCall&) = delete;
			DrawCall& operator=(const DrawCall&) = delete;
		};

		std::vector<DrawCall> _drawCalls;
		bool _beginCalled;
	public:
		MeshBatcher(IGraphicsDevice* device);

		MeshBatcher(const MeshBatcher&) = delete;
		MeshBatcher& operator=(const MeshBatcher&) = delete;

		MeshBatcher(MeshBatcher&&) noexcept = default;
		MeshBatcher& operator=(MeshBatcher&&) noexcept = default;

		/// <summary>
		/// Resets the graphics context state to be ready for batching meshes.
		/// </summary>
		void Begin();
		/// <summary>
		/// Submits an mesh part to be drawn.
		/// </summary>
		/// <param name="meshPart"></param>
		void Draw(ModelMeshPart* meshPart, RenderPassType passType = RenderPassType::Opaque);
		/// <summary>
		/// Draws all meshes.
		/// </summary>
		void End();
	};
}