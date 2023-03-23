#include "VertexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

VertexBuffer::VertexBuffer(
	_In_ GraphicsDevice* device,
	_In_ const void* data, 
	size_t p_structSize,
	size_t numVerticies,
	BufferUsage usage
):
	device(device),
	numVerts(numVerticies),
	structSize(p_structSize)
{
#ifdef _DX11
	D3D11_BUFFER_DESC vertexBuffDesc{};
	vertexBuffDesc.ByteWidth = UINT(structSize * numVerticies);
	vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBuffDesc.BindFlags = UINT(usage);
	vertexBuffDesc.StructureByteStride = UINT(structSize);

	D3D11_SUBRESOURCE_DATA resource{};
	resource.pSysMem = data;

	HRESULT r = device->device->CreateBuffer(&vertexBuffDesc, &resource, buffer.GetAddressOf());
	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create a vertex buffer!");
#endif
}

void VertexBuffer::SetData(void *data, size_t size)
{
#ifdef _DX11
	D3D11_MAPPED_SUBRESOURCE res{};
	res.pData = data;
	res.DepthPitch = (UINT)(size);

	HRESULT r = device->context->Map(buffer.Get(), 0, D3D11_MAP_READ_WRITE, 0, &res);
	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to write a vertex buffer!");
	
	device->context->Unmap(buffer.Get(), 0);
#endif
}

void VertexBuffer::Set()
{
#ifdef _DX11
	unsigned strides = (UINT)this->structSize;
	unsigned offsets = 0;
	this->device->context->IASetVertexBuffers(0, 1, this->buffer.GetAddressOf(), &strides, &offsets);
#endif // _DX11
}

void VertexBuffer::Draw(unsigned startIndex)
{
	Set();
#if _DX11
	device->context->Draw(UINT(numVerts), UINT(startIndex));
#endif
}

size_t VertexBuffer::TotalSize()
{
	return this->numVerts * this->structSize;
}
size_t VertexBuffer::StructSize()
{
	return this->structSize;
}
size_t VertexBuffer::NumVerticies()
{
	return this->numVerts;
}