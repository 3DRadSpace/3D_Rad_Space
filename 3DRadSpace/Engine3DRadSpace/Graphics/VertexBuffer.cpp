#include "VertexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

VertexBuffer::VertexBuffer(
	_In_ GraphicsDevice* device,
	_In_reads_bytes_(p_structSize * numVertices) const void* data,
	size_t p_structSize,
	size_t numVertices,
	BufferUsage usage
):
	_device(device),
	_numVerts(numVertices),
	_structSize(p_structSize)
{
#ifdef _DX11
	D3D11_BUFFER_DESC vertexBuffDesc{};
	vertexBuffDesc.ByteWidth = UINT(_structSize * numVertices);
	vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.StructureByteStride = UINT(_structSize);

	D3D11_SUBRESOURCE_DATA resource{};
	resource.pSysMem = data;

	HRESULT r = device->_device->CreateBuffer(&vertexBuffDesc, &resource, _buffer.GetAddressOf());
	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create a vertex buffer!");
#endif
}

void VertexBuffer::SetData(void *data, size_t size)
{
#ifdef _DX11
	D3D11_MAPPED_SUBRESOURCE res{};
	res.pData = data;
	res.DepthPitch = (UINT)(size);

	HRESULT r = _device->_context->Map(_buffer.Get(), 0, D3D11_MAP_READ_WRITE, 0, &res);
	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to write a vertex buffer!");
	
	_device->_context->Unmap(_buffer.Get(), 0);
#endif
}

void VertexBuffer::Set()
{
#ifdef _DX11
	unsigned strides = (UINT)this->_structSize;
	unsigned offsets = 0;
	this->_device->_context->IASetVertexBuffers(0, 1, _buffer.GetAddressOf(), &strides, &offsets);
#endif // _DX11
}

void VertexBuffer::Draw(unsigned startIndex)
{
	Set();
#if _DX11
	_device->_context->Draw(UINT(_numVerts), UINT(startIndex));
#endif
}

size_t VertexBuffer::TotalSize()
{
	return _numVerts * _structSize;
}
size_t VertexBuffer::StructSize()
{
	return _structSize;
}
size_t VertexBuffer::NumVertices()
{
	return _numVerts;
}