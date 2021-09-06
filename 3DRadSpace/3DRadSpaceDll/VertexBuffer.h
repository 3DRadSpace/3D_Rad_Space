#include "Globals.h"
#include "Vector4.h"
#include "Color.h"
#pragma once

#ifdef __DIRECTXVER

#include <d3d11.h>

struct VertexPositionDeclaration
{
	Vector4 Pos;
};

struct VertexPositionColorDeclaration
{
	Vector4 Pos;
	ColorShader Color;
};

struct VertexPositionNormalDeclaration
{
	Vector4 Pos;
	Vector4 Normal;
};

struct VertexPositionNormalColorDeclaration
{
	Vector4 Pos;
	Vector4 Normal;
	ColorShader Color;
};

template<class T>
class VertexBuffer
{
	T* data;
	size_t size;
	bool _vertexbuffercreated;
	ID3D11Buffer* _buffer;
public:
	VertexBuffer(T vertexdata[]) : data(vertexdata), size(sizeof(vertexdata) / sizeof(T)) , _buffer(nullptr),_vertexbuffercreated(false) {};
	VertexBuffer(T* vertexdata, size_t size) : data(vertexdata), size(size) , _buffer(nullptr), _vertexbuffercreated(false) {};
	VertexBuffer(const std::initializer_list<T> &data);

	void CreateVertexBuffer(ID3D11Device* dev);
	ID3D11Buffer* GetCreatedVertexBuffer() noexcept;

	void Draw(ID3D11DeviceContext* context);

	~VertexBuffer();
};

template<class T>
VertexBuffer<T>::VertexBuffer(const std::initializer_list<T>& list)
{
	static_assert(std::is_class<T>::value, "T must be a struct/class");

	this->_buffer = nullptr;
	this->_vertexbuffercreated = false;

	//maive memcpy literally
	this->size = list.size();
	this->data = new T[list.size()];

	for (int i = 0; i < this->size; i++)
	{
		this->data[i] = list[i];
	}
}

template<class T>
inline VertexBuffer<T>::~VertexBuffer()
{
	delete[] this->data;

	_buffer->Release();
}

template<class T>
void VertexBuffer<T>::CreateVertexBuffer(ID3D11Device* dev)
{
	if (this->_vertexbuffercreated) return;

	D3D11_BUFFER_DESC buffDesc;
	memset(&buffDesc, 0, sizeof(D3D11_BUFFER_DESC));
	buffDesc.ByteWidth = sizeof(T) * this->size;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA buffFiller;
	memset(&buffFiller, 0, sizeof(D3D11_SUBRESOURCE_DATA));
	buffFiller.pSysMem = this->data;

	HRESULT r = dev->CreateBuffer(&buffDesc, &buffFiller, &this->_buffer);

	if (FAILED(r))
	{
		const type_info &ti = typeid(ID3D11Device);
		throw ResourceCreationException("Failed to create a vertex buffer.", ti);
	}

	this->_vertexbuffercreated = true;

}

template<class T>
ID3D11Buffer* VertexBuffer<T>::GetCreatedVertexBuffer() noexcept
{
	return this->_vertexbuffercreated ? this->_buffer : nullptr;
}

template<class T>
void VertexBuffer<T>::Draw(ID3D11DeviceContext* context)
{
	unsigned offset = 0;
	unsigned stride = sizeof(T);

	context->IASetVertexBuffers(0, 1, &this->_buffer, &stride, &offset);
	context->Draw(this->size, 0);
}

#endif
