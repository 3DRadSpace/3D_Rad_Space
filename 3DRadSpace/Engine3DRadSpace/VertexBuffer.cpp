#include "VertexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

VertexBuffer<Engine3DRadSpace::Graphics::UnspecifiedVertexDecl>::VertexBuffer(_In_ GraphicsDevice * device,_In_ const void *data, size_t size, BufferUsage usage):
	_device(device),
	bufferSize(size)
{
#ifdef _DX11
	D3D11_BUFFER_DESC vertexBuffDesc{};
	vertexBuffDesc.ByteWidth = static_cast<UINT>(bufferSize);
	vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBuffDesc.BindFlags = static_cast<UINT>(usage);

	D3D11_SUBRESOURCE_DATA resource{};
	resource.pSysMem = data;

	HRESULT r = device->_device->CreateBuffer(&vertexBuffDesc, &resource, _buffer.GetAddressOf());
	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create a vertex buffer!");
#endif
}

void VertexBuffer<UnspecifiedVertexDecl>::SetData(void *data, size_t size)
{
#ifdef _DX11
	D3D11_MAPPED_SUBRESOURCE res{};
	res.pData = data;
	res.DepthPitch = static_cast<UINT>(size);

	HRESULT r = _device->_context->Map(_buffer.Get(), 0, D3D11_MAP_READ_WRITE, 0, &res);
	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to write a vertex buffer!");
	
	_device->_context->Unmap(_buffer.Get(), 0);
#endif
}
