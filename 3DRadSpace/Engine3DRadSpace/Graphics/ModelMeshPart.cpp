#include "ModelMeshPart.hpp"
#include <memory>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

ModelMeshPart::ModelMeshPart(
	Engine3DRadSpace::Graphics::Shaders::ShaderPipeline *shaders,
	Engine3DRadSpace::Graphics::VertexBuffer *vert, 
	Engine3DRadSpace::Graphics::IndexBuffer *buffer):
	_device(vert->_device),
	VertexBuffer(vert),
	IndexBuffer(buffer),
	Transform(Engine3DRadSpace::Math::Matrix())
{
}

ModelMeshPart::ModelMeshPart(ShaderPipeline *shaders, GraphicsDevice *Device,
	void *vertices, size_t numVerts, size_t structSize, std::span<unsigned> indices):
	_device(Device),
	Transform(Engine3DRadSpace::Math::Matrix())
{
	VertexBuffer = std::make_unique<Engine3DRadSpace::Graphics::VertexBuffer>(Device, vertices, structSize, numVerts);
	IndexBuffer = std::make_unique<Engine3DRadSpace::Graphics::IndexBuffer>(Device, indices);
}

ModelMeshPart::ModelMeshPart(ModelMeshPart&& meshPart) noexcept :
	_device(meshPart._device),
	VertexBuffer(std::move(meshPart.VertexBuffer)),
	IndexBuffer(std::move(meshPart.IndexBuffer)),
	Transform(meshPart.Transform),
	Textures(std::move(meshPart.Textures))
{
}

ModelMeshPart& ModelMeshPart::operator=(ModelMeshPart&& meshPart) noexcept
{
	_device = meshPart._device;
	IndexBuffer = std::move(meshPart.IndexBuffer);
	VertexBuffer = std::move(meshPart.VertexBuffer);
	Textures = std::move(meshPart.Textures);

	return *this;
}

void ModelMeshPart::Draw()
{
	_shaders->SetAll();

	for(int i = 0; i < Textures.size(); i++)
	{
		auto vertexShader = _shaders->GetVertexShader();
		if(vertexShader != nullptr)
			vertexShader->SetTexture(i, Textures[i].get());

		auto hullShader = _shaders->GetHullShader();
		if(hullShader != nullptr)
			hullShader->SetTexture(i, Textures[i].get());

		auto domainShader = _shaders->GetDomainShader();
		if(domainShader != nullptr)
			domainShader->SetTexture(i, Textures[i].get());

		auto geometryShader = _shaders->GetGeometryShader();
		if(geometryShader != nullptr)
			geometryShader->SetTexture(i, Textures[i].get());

		auto pixelShader = _shaders->GetPixelShader();
		if(pixelShader != nullptr)
			pixelShader->SetTexture(i, Textures[i].get());
	}

	//TODO: continue setting the input assembler
}
