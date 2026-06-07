#pragma once
#include "../ModelMeshPart.hpp"
#include "RenderPassType.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IGraphicsDevice;
	class IGraphicsCommandList;

	class ModelMesh;
	class Model3D;
}

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Manages batching meshes using plain or instanced drawing calls.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT MeshBatcher
	{
		IGraphicsDevice* _device;

		struct InstanceDataEntry
		{
			std::unique_ptr<std::byte[]> Data;
			size_t SizeInBytes; 
			int BufferID;
		};

		struct DrawCall
		{
			ModelMeshPart* MeshPart;
			std::vector<Math::Matrix4x4> Transforms;
			std::vector<InstanceDataEntry> InstanceData;
			Effect* BoundEffect;
			RenderPassType PassType;

			DrawCall();
			DrawCall(DrawCall&&) noexcept = default;
			DrawCall& operator=(DrawCall&&) noexcept = default;

			DrawCall(const DrawCall&) = delete;
			DrawCall& operator=(const DrawCall&) = delete;

			void Draw(IGraphicsCommandList* context, Effect* effect, size_t idxTransform);
			void Draw(IGraphicsCommandList* context, size_t idxTransform);
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
		void Draw(ModelMeshPart* meshPart, Effect* effect = nullptr, RenderPassType passType = RenderPassType::Opaque);
		void Draw(ModelMesh* mesh, Effect* effect = nullptr, RenderPassType passType = RenderPassType::Opaque);
		void Draw(Model3D* model, Effect* effect = nullptr, RenderPassType passType = RenderPassType::Opaque);
		/// <summary>
		/// Draws all meshes.
		/// </summary>
		void DrawAll();

		/// <summary>
		/// Erases the internal mesh list.
		/// </summary>
		void End();
	};
}