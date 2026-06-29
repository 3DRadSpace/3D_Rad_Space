#include "ModelMeshPart.hpp"
#include "Effect.hpp"
#include "../Graphics/IGraphicsCommandList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

ModelMeshPart::ModelMeshPart(
	Graphics::IVertexBuffer *vert, 
	Graphics::IIndexBuffer *index,
	Effect* shaders
):
	_device(vert->GetGraphicsDevice()),
	VertexBuffer(vert),
	IndexBuffer(index),
	_shaders(shaders)
{
}

ModelMeshPart::ModelMeshPart(
	IGraphicsDevice *Device, 
	void *vertices,
	size_t numVerts,
	size_t structSize, 
	std::span<unsigned> indices,
	Effect* shaders
):
	_device(Device),
	_shaders(shaders)
{
	VertexBuffer = Device->CreateVertexBuffer(vertices, structSize, numVerts, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
	IndexBuffer = Device->CreateIndexBuffer(indices);
}

void ModelMeshPart::Draw()
{
	Draw(_shaders);
}

void ModelMeshPart::Draw(Effect* effect)
{
	if(_device == nullptr) return;
	if(effect == nullptr) return;

	effect->SetAll();
	effect->SetData<Math::Matrix4x4>(&Transform, 0, 0);

	for(int i = 0; i < Textures.size(); i++)
	{
		effect->SetTexture(Textures[i].get(), i);
		effect->SetSampler(TextureSamplers[i].get(), i);
	}

	auto cmdList = _device->ImmediateContext();

	cmdList->SetTopology(VertexTopology::TriangleList);
	cmdList->DrawVertexBufferWithindices(VertexBuffer.get(), IndexBuffer.get());
}

BoundingSphere ModelMeshPart::GetBoundingSphere() const noexcept
{
	return _sphere;
}

IVertexBuffer* ModelMeshPart::GetVertexBuffer() const noexcept
{
	return VertexBuffer.get();
}

IIndexBuffer* ModelMeshPart::GetIndexBuffer() const noexcept
{
	return IndexBuffer.get();
}

BoundingBox ModelMeshPart::GetBoundingBox() const noexcept
{
	return _box;
}

Effect *ModelMeshPart::GetShaders() const noexcept
{
	return _shaders;
}

void ModelMeshPart::SetShaders(Effect *shaders)
{
	_shaders = shaders;
}

std::pair<IVertexBuffer*, IIndexBuffer*> ModelMeshPart::CreateStagingBuffers()
{
	if(!_stagingVertex)
	{
		_stagingVertex = VertexBuffer->CreateStaging();
	}
	
	if(!_stagingIndex)
	{
		_stagingIndex = IndexBuffer->CreateStaging();
	}

	return std::make_pair<IVertexBuffer*, IIndexBuffer*>(
		_stagingVertex.get(),
		_stagingIndex.get()
	);
}