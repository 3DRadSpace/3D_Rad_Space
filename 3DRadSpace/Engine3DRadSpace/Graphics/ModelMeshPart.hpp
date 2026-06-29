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

namespace Engine3DRadSpace::Graphics
{
	class Model3D;
	class Effect;

	/// <summary>
	/// Represents a mesh formed by a index and vertex buffer, plus an effect.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ModelMeshPart
	{
		IGraphicsDevice* _device;

		Effect* _shaders;

		Math::BoundingBox _box;
		Math::BoundingSphere _sphere;

		std::unique_ptr<IVertexBuffer> _stagingVertex;
		std::unique_ptr<IIndexBuffer> _stagingIndex;
	public:
		std::unique_ptr<IIndexBuffer> IndexBuffer;
		std::unique_ptr<IVertexBuffer> VertexBuffer;

		ModelMeshPart(
			Graphics::IVertexBuffer* vert, 
			Graphics::IIndexBuffer* index,
			Effect* shaders
		);

		ModelMeshPart(
			IGraphicsDevice *Device,
			void* vertices, 
			size_t numVerts,
			size_t structSize, 
			std::span<unsigned> indices,
			Effect* shaders
		);

		ModelMeshPart(ModelMeshPart&& meshPart) noexcept = default;
		ModelMeshPart(ModelMeshPart& meshPart) = delete;

		ModelMeshPart& operator=(ModelMeshPart&) = delete;
		ModelMeshPart& operator=(ModelMeshPart&& meshPart) noexcept = default;

		template<VertexDecl V>
		ModelMeshPart(
			IGraphicsDevice* Device,
			std::span<V> vertices,
			std::span<unsigned> indices,
			Effect *shaders
		);

		Math::Matrix4x4 Transform = Math::Matrix4x4();
		std::vector<std::unique_ptr<ITexture2D>> Textures;
		std::vector<std::unique_ptr<ISamplerState>> TextureSamplers;

		void Draw();
		void Draw(Effect* effect);

		Math::BoundingBox GetBoundingBox() const noexcept;
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		Graphics::IVertexBuffer* GetVertexBuffer() const noexcept;
		Graphics::IIndexBuffer* GetIndexBuffer() const noexcept;

		Effect* GetShaders() const noexcept;
		void SetShaders(Effect *shaders);

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
		std::span<unsigned> indices,
		Effect *shaders
	):
		_device(Device),
		_shaders(shaders)
	{
		VertexBuffer = _device->CreateVertexBuffer<V>(vertices, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
		IndexBuffer = _device->CreateIndexBuffer(indices);
	}
}