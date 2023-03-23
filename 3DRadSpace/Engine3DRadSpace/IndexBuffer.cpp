#include "IndexBuffer.hpp"
#include "GraphicsDevice.hpp"
#include "Error.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;

IndexBuffer::IndexBuffer(GraphicsDevice* device,std::span<unsigned> indicies):
	device(device)
{
#ifdef WIN32
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(indicies.size() * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = &indicies[0];

	HRESULT r = device->device->CreateBuffer(&desc, &data, &indexBuffer);
	RaiseFatalErrorIfFailed(r, "Failed to create a index buffer!");
#endif
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, unsigned* indicies, size_t numIndicies):
	device(device)
{
#ifdef WIN32
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(numIndicies * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = indicies;

	HRESULT r = device->device->CreateBuffer(&desc, &data, &indexBuffer);
	RaiseFatalErrorIfFailed(r, "Failed to create a index buffer!");
#endif
}

void Engine3DRadSpace::Graphics::IndexBuffer::Set(std::span<unsigned> newIndicies)
{
#ifdef _DX11
	
#endif
}
