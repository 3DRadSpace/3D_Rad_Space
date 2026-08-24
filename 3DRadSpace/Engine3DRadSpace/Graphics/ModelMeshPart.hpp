#pragma once
#include "IGraphicsDevice.hpp"
#include "IVertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "ISamplerState.hpp"
#include "ITexture2D.hpp"
#include "VertexDeclarations.hpp"
#include "../Math/BoundingSphere.hpp"
#include "../Math/BoundingBox.hpp"
#include "IGraphicsCommandList.hpp"
#include "Rendering/MaterialDescriptor.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D;
	class Effect;

	/// <summary>
	/// Represents a mesh formed by a index and vertex buffer, plus an effect. Bounding box and bounding sphere are also stored for frustum culling.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ModelMeshPart
	{
		IGraphicsDevice* _device;

		Math::BoundingBox _box;
		Math::BoundingSphere _sphere;

		std::unique_ptr<IVertexBuffer> _stagingVertex;
		std::unique_ptr<IIndexBuffer> _stagingIndex;
	public:
		std::unique_ptr<IIndexBuffer> IndexBuffer;
		std::unique_ptr<IVertexBuffer> VertexBuffer;

		/// <summary>
		/// Constructs a model mesh part with specified GPU vertex and index buffers.
		/// </summary>
		/// <param name="vert">The GPU vertex buffer.</param>
		/// <param name="index">The GPU index buffer.</param>
		ModelMeshPart(
			Graphics::IVertexBuffer* vert, 
			Graphics::IIndexBuffer* index
		);

		/// <summary>
		/// Constructs a model mesh part with specified CPU vertex buffers.
		/// </summary>
		/// <param name="Device">The graphics device.</param>
		/// <param name="vertices">The vertex data.</param>
		/// <param name="numVerts">The number of vertices.</param>
		/// <param name="structSize">The size of each vertex structure.</param>
		/// <param name="indices"></param>
		ModelMeshPart(
			IGraphicsDevice *Device,
			void* vertices, 
			size_t numVerts,
			size_t structSize, 
			std::span<unsigned> indices
		);

		ModelMeshPart(ModelMeshPart&& meshPart) noexcept = default;
		ModelMeshPart(ModelMeshPart& meshPart) = delete;

		ModelMeshPart& operator=(ModelMeshPart&) = delete;
		ModelMeshPart& operator=(ModelMeshPart&& meshPart) noexcept = default;

		/// <summary>
		/// Constructs a model mesh part with specified vertex format.
		/// </summary>
		/// <typeparam name="V">The vertex declaration type.</typeparam>
		/// <param name="Device">The graphics device.</param>
		/// <param name="vertices">The vertex data.</param>
		/// <param name="indices">The index data.</param>
		template<VertexDecl V>
		ModelMeshPart(
			IGraphicsDevice* Device,
			std::span<V> vertices,
			std::span<unsigned> indices
		);

		/// <summary>
		///	Import offset set by the model importer.
		/// </summary>
		Math::Matrix4x4 ImportOffset = Math::Matrix4x4();
		/// <summary>
		/// World/Model transform matrix.
		/// </summary>
		Math::Matrix4x4 World = Math::Matrix4x4();
		/// <summary>
		/// Assigned view matrix. Usually obtained from the selected camera.
		/// </summary>
		Math::Matrix4x4 View = Math::Matrix4x4();
		/// <summary>
		/// Assigned projection matrix. Usually obtained from the selected camera.
		/// </summary>
		Math::Matrix4x4 Projection = Math::Matrix4x4();
		/// <summary>
		/// Describes the material properties of this mesh part.
		/// </summary>
		Rendering::MaterialDescriptor Material;

		/// <summary>
		/// Gets the combined Model-View-Projection matrix for this mesh part.
		/// </summary>
		/// <returns>The combined Model-View-Projection matrix.</returns>
		Math::Matrix4x4 MVP() const noexcept;

		/// <summary>
		/// All textures used by this mesh part. The order of the textures should match the order expected by the effect/shader.
		/// </summary>
		std::vector<std::unique_ptr<ITexture2D>> Textures;
		/// <summary>
		/// All sampler states used by the textures.
		/// </summary>
		std::vector<std::unique_ptr<ISamplerState>> TextureSamplers;

		/// <summary>
		/// Gets the bounding box of the mesh part. This is used for frustum culling and collision detection.
		/// </summary>
		/// <returns>The bounding box of the mesh part.</returns>
		Math::BoundingBox GetBoundingBox() const noexcept;
		/// <summary>
		/// Gets the bounding sphere of the mesh part. This is used for frustum culling and collision detection.
		/// </summary>
		/// <returns>The bounding sphere of the mesh part.</returns>
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		/// <summary>
		///	Gets the underlying vertex buffer of this mesh part.
		/// </summary>
		/// <returns></returns>
		Graphics::IVertexBuffer* GetVertexBuffer() const noexcept;
		/// <summary>
		///	Gets the underlying index buffer of this mesh part.
		/// </summary>
		/// <returns></returns>
		Graphics::IIndexBuffer* GetIndexBuffer() const noexcept;

		/// <summary>
		/// Creates staging vertex and index buffers available for CPU reading if they don't exist. If they already exist, returns the already created buffers.
		/// </summary>
		/// <returns>Pair of vertex and index buffers pointer references</returns>
		std::pair<Graphics::IVertexBuffer*, Graphics::IIndexBuffer*> CreateStagingBuffers();

		~ModelMeshPart() = default;

		friend class Model3D;
	};

	template<VertexDecl V>
	inline ModelMeshPart::ModelMeshPart(
		IGraphicsDevice* Device,
		std::span<V> vertices, 
		std::span<unsigned> indices
	):
		_device(Device)
	{
		VertexBuffer = _device->CreateVertexBuffer<V>(vertices, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
		IndexBuffer = _device->CreateIndexBuffer(indices);
	}
}