#include "ModelMeshPart.hpp"

using namespace Engine3DRadSpace::Graphics;

ModelMeshPart::ModelMeshPart(Engine3DRadSpace::Graphics::VertexBuffer* vert, Engine3DRadSpace::Graphics::IndexBuffer* buffer):
	VertexBuffer(vert),
	IndexBuffer(buffer),
	device(vert->device),
	Transform(Engine3DRadSpace::Math::Matrix())
{
}

ModelMeshPart::ModelMeshPart(GraphicsDevice* Device, void* vertices, size_t numVerts, size_t structSize, std::span<unsigned> indices):
	device(Device),
	Transform(Engine3DRadSpace::Math::Matrix())
{
	VertexBuffer = std::make_unique<Engine3DRadSpace::Graphics::VertexBuffer>(Device, vertices, structSize, numVerts);
	IndexBuffer = std::make_unique<Engine3DRadSpace::Graphics::IndexBuffer>(Device, indices);
}

Engine3DRadSpace::Graphics::ModelMeshPart::ModelMeshPart(ModelMeshPart&& meshPart) noexcept :
	device(meshPart.device),
	VertexBuffer(std::move(meshPart.VertexBuffer)),
	IndexBuffer(std::move(meshPart.IndexBuffer)),
	Transform(meshPart.Transform)
{
}

ModelMeshPart& Engine3DRadSpace::Graphics::ModelMeshPart::operator=(ModelMeshPart&& meshPart) noexcept
{
	this->device = meshPart.device;
	this->IndexBuffer = std::move(meshPart.IndexBuffer);
	this->VertexBuffer = std::move(meshPart.VertexBuffer);
	return *this;
}

void ModelMeshPart::Draw()
{
	device->DrawVertexBufferWithindices(VertexBuffer.get(), IndexBuffer.get());
}
