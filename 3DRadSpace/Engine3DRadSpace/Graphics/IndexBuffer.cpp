#include "IndexBuffer.hpp"
#include "../GraphicsDevice.hpp"
#include "../Logging/Error.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;

IndexBuffer::IndexBuffer(GraphicsDevice* device,std::span<unsigned> indices):
	_device(device),
	_numIndices(indices.size())
{
#ifdef _DX11
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(indices.size() * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = &indices[0];

	HRESULT r = device->_device->CreateBuffer(&desc, &data, &_indexBuffer);
	RaiseFatalErrorIfFailed(r, "Failed to create a index buffer!");
#endif
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices):
	_device(device),
	_numIndices(numindices)
{
#ifdef _DX11
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(numindices * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = indices;

	HRESULT r = device->_device->CreateBuffer(&desc, &data, &_indexBuffer);
	RaiseFatalErrorIfFailed(r, "Failed to create a index buffer!");
#endif
}

void Engine3DRadSpace::Graphics::IndexBuffer::SetData(std::span<unsigned> newindices)
{
#ifdef _DX11
	D3D11_MAPPED_SUBRESOURCE mappedBuff{};
	HRESULT r = _device->_context->Map(_indexBuffer.Get(), 0, D3D11_MAP_WRITE, 0, &mappedBuff);
	Logging::RaiseFatalErrorIfFailed(r, "Failed to map a index buffer!");
	memcpy(mappedBuff.pData, &newindices[0], newindices.size_bytes());
	_device->_context->Unmap(_indexBuffer.Get(), 0);
#endif
}

unsigned Engine3DRadSpace::Graphics::IndexBuffer::NumIndices() const
{
	return _numIndices;
}

void Engine3DRadSpace::Graphics::IndexBuffer::Set(unsigned offset)
{
#ifdef _DX11
	_device->_context->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
#endif
}
