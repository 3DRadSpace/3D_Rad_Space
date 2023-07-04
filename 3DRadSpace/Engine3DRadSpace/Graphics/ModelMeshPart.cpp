#include "ModelMeshPart.hpp"
#include <memory>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

ModelMeshPart::ModelMeshPart(
	Engine3DRadSpace::Graphics::Shaders::ShaderPipeline *shaders,
	Engine3DRadSpace::Graphics::VertexBuffer *vert, 
	Engine3DRadSpace::Graphics::IndexBuffer *buffer):
	_device(vert->_device),
	VertexBuffer(vert),
	IndexBuffer(buffer),
	_shaders(nullptr)
{
}

ModelMeshPart::ModelMeshPart(ShaderPipeline *shaders, GraphicsDevice *Device,
	void *vertices, size_t numVerts, size_t structSize, std::span<unsigned> indices):
	_device(Device),
	_shaders(shaders)
{
	VertexBuffer = std::make_unique<Engine3DRadSpace::Graphics::VertexBuffer>(Device, vertices, structSize, numVerts);
	IndexBuffer = std::make_unique<Engine3DRadSpace::Graphics::IndexBuffer>(Device, indices);
}

ModelMeshPart::ModelMeshPart(ModelMeshPart&& meshPart) noexcept :
	_device(meshPart._device),
	VertexBuffer(std::move(meshPart.VertexBuffer)),
	IndexBuffer(std::move(meshPart.IndexBuffer)),
	Transform(meshPart.Transform),
	Textures(std::move(meshPart.Textures)),
	TextureSamplers(std::move(meshPart.TextureSamplers)),
	_shaders(meshPart._shaders)
{
}

ModelMeshPart& ModelMeshPart::operator=(ModelMeshPart&& meshPart) noexcept
{
	_device = meshPart._device;
	_shaders = meshPart._shaders;
	IndexBuffer = std::move(meshPart.IndexBuffer);
	VertexBuffer = std::move(meshPart.VertexBuffer);
	Textures = std::move(meshPart.Textures);
	TextureSamplers = std::move(meshPart.TextureSamplers);
	Transform = meshPart.Transform;

	return *this;
}

void ModelMeshPart::Draw()
{
	_shaders->SetAll();

	for(int i = 0; i < Textures.size(); i++)
	{
		auto vertexShader = _shaders->GetVertexShader();
		if(vertexShader != nullptr)
		{
			vertexShader->SetTexture(i, Textures[i].get());
			vertexShader->SetSampler(i, TextureSamplers[i].get());
			vertexShader->SetData(0, &Transform, sizeof(Matrix));
		}

		auto hullShader = _shaders->GetHullShader();
		if(hullShader != nullptr)
		{
			hullShader->SetTexture(i, Textures[i].get());
			hullShader->SetSampler(i, TextureSamplers[i].get());
			hullShader->SetData(0, &Transform, sizeof(Matrix));
		}

		auto domainShader = _shaders->GetDomainShader();
		if(domainShader != nullptr)
		{
			domainShader->SetTexture(i, Textures[i].get());
			domainShader->SetSampler(i, TextureSamplers[i].get());
			domainShader->SetData(0, &Transform, sizeof(Matrix));
		}

		auto geometryShader = _shaders->GetGeometryShader();
		if(geometryShader != nullptr)
		{
			geometryShader->SetTexture(i, Textures[i].get());
			geometryShader->SetSampler(i, TextureSamplers[i].get());
			geometryShader->SetData(0, &Transform, sizeof(Matrix));
		}

		auto pixelShader = _shaders->GetPixelShader();
		if(pixelShader != nullptr)
		{
			pixelShader->SetTexture(i, Textures[i].get());
			pixelShader->SetSampler(i, TextureSamplers[i].get());
			pixelShader->SetData(0, &Transform, sizeof(Matrix));
		}
	}

	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawVertexBufferWithindices(VertexBuffer.get(), IndexBuffer.get());
}

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline *Engine3DRadSpace::Graphics::ModelMeshPart::GetShaders()
{
	return _shaders;
}
