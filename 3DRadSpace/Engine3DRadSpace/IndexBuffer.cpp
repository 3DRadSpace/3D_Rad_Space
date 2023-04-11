#include "IndexBuffer.hpp"
#include "GraphicsDevice.hpp"
#include "Error.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;

IndexBuffer::IndexBuffer(GraphicsDevice* device,std::span<unsigned> indices):
	device(device)
{
#ifdef _DX11
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(indices.size() * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = &indices[0];

	HRESULT r = device->device->CreateBuffer(&desc, &data, &indexBuffer);
	RaiseFatalErrorIfFailed(r, "Failed to create a index buffer!");
#endif
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices):
	device(device)
{
#ifdef _DX11
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(numindices * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = indices;

	HRESULT r = device->device->CreateBuffer(&desc, &data, &indexBuffer);
	RaiseFatalErrorIfFailed(r, "Failed to create a index buffer!");
#endif
}

void Engine3DRadSpace::Graphics::IndexBuffer::SetData(std::span<unsigned> newindices)
{
#ifdef _DX11
	D3D11_MAPPED_SUBRESOURCE mappedBuff{};
	HRESULT r = device->context->Map(indexBuffer.Get(), 0, D3D11_MAP_WRITE, 0, &mappedBuff);
	Logging::RaiseFatalErrorIfFailed(r, "Failed to map a index buffer!");
	memcpy(mappedBuff.pData, &newindices[0], newindices.size_bytes());
	device->context->Unmap(indexBuffer.Get(), 0);
#endif
}

void Engine3DRadSpace::Graphics::IndexBuffer::Set(unsigned offset)
{
#ifdef _DX11
	device->context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
#endif
}
