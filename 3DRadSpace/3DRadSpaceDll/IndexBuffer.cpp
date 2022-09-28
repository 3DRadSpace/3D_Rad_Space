#include "IndexBuffer.hpp"

Engine3DRadSpace::IndexBuffer::IndexBuffer(unsigned int* indexes, size_t size)
{
	this->_indexes = indexes;
	this->_size = size;
	this->_createdbuffer = false;
	this->_indexbuffer = nullptr;
}

Engine3DRadSpace::IndexBuffer::IndexBuffer(const std::vector<unsigned int> &initializer)
{
	this->_createdbuffer = false;
	this->_indexbuffer = nullptr;

	size_t l = initializer.size();
	this->_indexes = new unsigned int[l];
	this->_size = l;

	//again a naive mem copy

	for (size_t i = 0; i < l; i++)
	{
		this->_indexes[i] = initializer[i];
	}
}

ID3D11Buffer* Engine3DRadSpace::IndexBuffer::GetCreatedBuffer()
{
	return this->_createdbuffer ? this->_indexbuffer : nullptr;
}

void Engine3DRadSpace::IndexBuffer::CreateIndexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.ByteWidth = sizeof(unsigned int) * this->_size;
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	//bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA bufferFiller;
	memset(&bufferFiller, 0, sizeof(D3D11_SUBRESOURCE_DATA));
	bufferFiller.pSysMem = this->_indexes;

	HRESULT r = device->CreateBuffer(&bufferDesc, &bufferFiller, &this->_indexbuffer);
	if (FAILED(r))
		throw ResourceCreationException("Failed to create a IndexBuffer");
	else
		this->_createdbuffer = true;
}

Engine3DRadSpace::IndexBuffer::~IndexBuffer()
{
	if (this->_indexbuffer != nullptr) this->_indexbuffer->Release();
	delete[] this->_indexes;

	this->_indexbuffer = nullptr;
	this->_indexes = nullptr;
}
