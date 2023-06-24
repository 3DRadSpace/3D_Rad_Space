#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "ShaderPipeline.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ModelMeshPart
	{
		GraphicsDevice* _device;

		Engine3DRadSpace::Graphics::Shaders::ShaderPipeline *_shaders;
	public:
		std::unique_ptr<Engine3DRadSpace::Graphics::IndexBuffer> IndexBuffer;
		std::unique_ptr<Engine3DRadSpace::Graphics::VertexBuffer> VertexBuffer;

		ModelMeshPart(
			Engine3DRadSpace::Graphics::Shaders::ShaderPipeline* shaders,
			Engine3DRadSpace::Graphics::VertexBuffer* vert, 
			Engine3DRadSpace::Graphics::IndexBuffer* buffer
		);

		ModelMeshPart(
			Engine3DRadSpace::Graphics::Shaders::ShaderPipeline *shaders, 
			GraphicsDevice* Device, 
			void* vertices, size_t numVerts, size_t structSize, 
			std::span<unsigned> indices
		);

		ModelMeshPart(ModelMeshPart&& meshPart) noexcept;
		ModelMeshPart(ModelMeshPart& meshPart) = delete;

		ModelMeshPart& operator=(ModelMeshPart&) = delete;
		ModelMeshPart& operator=(ModelMeshPart&& meshPart) noexcept;

		template<Engine3DRadSpace::Graphics::VertexDecl V>
		ModelMeshPart(
			Engine3DRadSpace::Graphics::Shaders::ShaderPipeline* shaders,
			Engine3DRadSpace::GraphicsDevice* Device,
			std::span<V> vertices, std::span<unsigned> indices
		);

		Engine3DRadSpace::Math::Matrix Transform = Engine3DRadSpace::Math::Matrix();
		std::vector<std::unique_ptr<Engine3DRadSpace::Graphics::Texture2D>> Textures;
		std::vector<std::unique_ptr<Engine3DRadSpace::Graphics::SamplerState>> TextureSamplers;

		void Draw();

		Engine3DRadSpace::Graphics::Shaders::ShaderPipeline *GetShaders();
	};

	template<Engine3DRadSpace::Graphics::VertexDecl V>
	inline ModelMeshPart::ModelMeshPart(
		Engine3DRadSpace::Graphics::Shaders::ShaderPipeline* shaders,
		Engine3DRadSpace::GraphicsDevice* Device, std::span<V> vertices, std::span<unsigned> indices ):
		_device(Device)
	{
		VertexBuffer = std::make_unique<Engine3DRadSpace::Graphics::VertexBufferV<V>>(Device, vertices);
		IndexBuffer = std::make_unique<Engine3DRadSpace::Graphics::IndexBuffer>(Device, indices);
	}

}

