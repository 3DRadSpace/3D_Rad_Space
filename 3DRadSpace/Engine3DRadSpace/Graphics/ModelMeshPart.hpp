#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "ShaderPipeline.hpp"
#include "../Math/BoundingSphere.hpp"
#include "../Math/BoundingBox.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT ModelMeshPart
	{
		GraphicsDevice* _device;

		std::shared_ptr<Shaders::ShaderPipeline> _shaders;

		Math::BoundingBox _box;
		Math::BoundingSphere _sphere;
	public:
		std::unique_ptr<IndexBuffer> IndexBuffer;
		std::unique_ptr<VertexBuffer> VertexBuffer;

		ModelMeshPart(
			std::shared_ptr<Shaders::ShaderPipeline> shaders,
			Graphics::VertexBuffer* vert, 
			Graphics::IndexBuffer* buffer
		);

		ModelMeshPart(
			GraphicsDevice *Device,
			std::shared_ptr<Shaders::ShaderPipeline> shaders, 
			void* vertices, size_t numVerts, size_t structSize, 
			std::span<unsigned> indices
		);

		ModelMeshPart(ModelMeshPart&& meshPart) noexcept;
		ModelMeshPart(ModelMeshPart& meshPart) = delete;

		ModelMeshPart& operator=(ModelMeshPart&) = delete;
		ModelMeshPart& operator=(ModelMeshPart&& meshPart) noexcept;

		template<VertexDecl V>
		ModelMeshPart(
			std::shared_ptr<Shaders::ShaderPipeline> shaders,
			GraphicsDevice* Device,
			std::span<V> vertices, std::span<unsigned> indices
		);

		Math::Matrix4x4 Transform = Math::Matrix4x4();
		std::vector<std::unique_ptr<Texture2D>> Textures;
		std::vector<std::unique_ptr<SamplerState>> TextureSamplers;

		void Draw();

		Math::BoundingBox GetBoundingBox();
		Math::BoundingSphere GetBoundingSphere();

		Shaders::ShaderPipeline *GetShaders();
		void SetShaders(std::shared_ptr<Shaders::ShaderPipeline> shaders);

		~ModelMeshPart() = default;

		friend class Model3D;
	};

	template<VertexDecl V>
	inline ModelMeshPart::ModelMeshPart(
		std::shared_ptr<Shaders::ShaderPipeline> shaders,
		GraphicsDevice* Device, std::span<V> vertices, std::span<unsigned> indices ):
		_device(Device),
		_shaders(shaders)
	{
		VertexBuffer = std::make_unique<VertexBufferV<V>>(Device, vertices);
		IndexBuffer = std::make_unique<Graphics::IndexBuffer>(Device, indices);
	}

}

