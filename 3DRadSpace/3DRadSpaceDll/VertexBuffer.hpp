#include "Globals.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Color.hpp"
#pragma once

#ifdef __DIRECTXVER

#include <d3d11.h>

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a vertex declaration with 1 single position
	/// </summary>
	struct VertexPositionDeclaration
	{
		/// <summary>
		/// 3D position
		/// </summary>
		Vector3 Pos;
	};

	/// <summary>
	/// Represents a vertex declaration with 1 3D position and a vertex colour
	/// </summary>
	struct VertexPositionColorDeclaration
	{
		/// <summary>
		/// 3D vertex position
		/// </summary>
		Vector3 Pos;
		/// <summary>
		/// Vertex colour
		/// </summary>
		ColorShader Color;
	};

	/// <summary>
	/// Represents a vertex declaration with 1 position vector and 1 normal vector
	/// </summary>
	struct VertexPositionNormalDeclaration
	{
		/// <summary>
		/// Vertex position
		/// </summary>
		Vector4 Pos;
		/// <summary>
		/// Vertex normal
		/// </summary>
		Vector4 Normal;
	};

	/// <summary>
	/// Represents a vertex declaration with 1 position vector, 1 normal vector and 1 vertex colour
	/// </summary>
	struct VertexPositionNormalColorDeclaration
	{
		/// <summary>
		/// Vertex position
		/// </summary>
		Vector4 Pos;
		/// <summary>
		/// Vertex normal
		/// </summary>
		Vector4 Normal;
		/// <summary>
		/// Vertex colour
		/// </summary>
		ColorShader Color;
	};
	/// <summary>
	/// Represents a vertex declaration with 1 position vector, 1 normal and 1 UV coordinate
	/// </summary>
	struct VertexPositionNormalTextureDeclaration
	{
		/// <summary>
		/// Vertex position
		/// </summary>
		Vector4 Pos;
		/// <summary>
		/// Vertex normal
		/// </summary>
		Vector4 Normal;
		/// <summary>
		/// Vertex UV coordinates
		/// </summary>
		Vector4 UV;
	};

	/// <summary>
	/// Represents a vector declaration with a potision, normal, UV and a vertex shader
	/// </summary>
	struct VertexPositionNormalTextureColorDeclaration
	{
		/// <summary>
		/// Vertex position
		/// </summary>
		Vector4 Pos;
		/// <summary>
		/// Vertex normal
		/// </summary>
		Vector4 Normal;
		/// <summary>
		/// UV texture coordinates
		/// </summary>
		Vector4 UV;
		/// <summary>
		/// Vertex colour
		/// </summary>
		ColorShader Color;
	};

	/// <summary>
	/// Represents a vector with position, normal, tangent, bitangent and UV texture coordinates
	/// </summary>
	struct VertexPositionNormalTextureTangentBitangentDeclaration
	{
		/// <summary>
		/// Position vector
		/// </summary>
		Vector4 Pos;
		/// <summary>
		/// Normal vector
		/// </summary>
		Vector4 Normal;
		/// <summary>
		/// UV texture coordintaes
		/// </summary>
		Vector4 UV;
		/// <summary>
		/// Tangent vector
		/// </summary>
		Vector4 Tangent;
		/// <summary>
		/// Bitangent vector
		/// </summary>
		Vector4 Bitangent;
	};

	/// <summary>
	/// Represents a vertex buffer
	/// </summary>
	/// <typeparam name="T">Any Vertex<X>Declaration struct, or void if unknown</typeparam>
	template<class T>
	class VertexBuffer
	{
		T* data;
		size_t size;
		bool _vertexbuffercreated;
		ID3D11Buffer* _buffer;
	public:
		/// <summary>
		/// Constructs a vertex buffer from the given array
		/// </summary>
		/// <param name="vertexdata">vertex array</param>
		VertexBuffer(T vertexdata[]) : data(vertexdata), size(sizeof(vertexdata) / sizeof(T)), _buffer(nullptr), _vertexbuffercreated(false) {};
		/// <summary>
		/// Constructs a vertex buffer from a dynamic memory array
		/// </summary>
		/// <param name="vertexdata">Pointer to the beginning of the vertex data</param>
		/// <param name="size">Lenght of the array</param>
		VertexBuffer(T* vertexdata, size_t size) : data(vertexdata), size(size), _buffer(nullptr), _vertexbuffercreated(false) {};
		/// <summary>
		/// Constructs a vertex buffer from a initializer list
		/// </summary>
		/// <param name="data">Initializer list containing all verticies</param>
		VertexBuffer(const std::initializer_list<T>& data);

		/// <summary>
		/// Confirm the vertex buffer creation
		/// </summary>
		/// <param name="dev">Device handle</param>
		void CreateVertexBuffer(ID3D11Device* dev);
		/// <summary>
		/// Return a low level handle to the vertex buffer
		/// </summary>
		/// <returns></returns>
		ID3D11Buffer* GetCreatedVertexBuffer() noexcept;

		/// <summary>
		/// Put the vertex buffer into command list then render it.
		/// <para>A shader must be set, otherwise errors are going to be thrown</para>
		/// </summary>
		/// <param name="context">Low level graphics device handle</param>
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
			const type_info& ti = typeid(ID3D11Device);
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

	template<class T>
	inline VertexBuffer<T>::~VertexBuffer()
	{
		delete[] this->data;

		_buffer->Release();
	}


	/// <summary>
	/// Represents a VertexBuffer with unknown type
	/// </summary>
	template<>
	class VertexBuffer<void>
	{
		void* data;
		size_t size;
		bool _vertexbuffercreated;
		ID3D11Buffer* _buffer;
		size_t _structsize;
	public:
		/// <summary>
		/// Constructs a vertex buffer from a memory buffer
		/// </summary>
		/// <param name="vertexdata">Memory buffer</param>
		/// <param name="total_size">Total size of the vertex buffer</param>
		/// <param name="stride">Size of an vertex element</param>
		VertexBuffer(void* vertexdata, size_t total_size, size_t stride) : data(vertexdata), size(total_size), _structsize(stride), _buffer(nullptr), _vertexbuffercreated(false) {};

		/// <summary>
		/// Confirms the creation of the vertex buffer
		/// </summary>
		/// <param name="dev"></param>
		void CreateVertexBuffer(ID3D11Device* dev);
		/// <summary>
		/// Returns a low level GAPI handle to the vertex buffer 
		/// </summary>
		/// <returns></returns>
		ID3D11Buffer* GetCreatedVertexBuffer() noexcept;

		/// <summary>
		/// Put the vertex buffer into command list then render it.
		/// <para>A shader must be set, otherwise errors are going to be thrown</para>
		/// </summary>
		/// <param name="context">Low level graphics device handle</param>
		void Draw(ID3D11DeviceContext* context);

		~VertexBuffer();
	};


	inline void VertexBuffer<void>::CreateVertexBuffer(ID3D11Device* dev)
	{
		if (this->_vertexbuffercreated) return;

		D3D11_BUFFER_DESC buffDesc;
		memset(&buffDesc, 0, sizeof(D3D11_BUFFER_DESC));
		buffDesc.ByteWidth = (unsigned)(this->_structsize * this->size);
		buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA buffFiller;
		memset(&buffFiller, 0, sizeof(D3D11_SUBRESOURCE_DATA));
		buffFiller.pSysMem = this->data;

		HRESULT r = dev->CreateBuffer(&buffDesc, &buffFiller, &this->_buffer);

		if (FAILED(r))
			throw ResourceCreationException("Failed to create a vertex buffer.", typeid(ID3D11Device));

		this->_vertexbuffercreated = true;
	}

	inline ID3D11Buffer* VertexBuffer<void>::GetCreatedVertexBuffer() noexcept
	{
		return this->_vertexbuffercreated ? this->_buffer : nullptr;
	}

	inline void VertexBuffer<void>::Draw(ID3D11DeviceContext* context)
	{
		unsigned offset = 0;
		unsigned stride = (unsigned)this->_structsize;

		context->IASetVertexBuffers(0, 1, &this->_buffer, &stride, &offset);
		context->Draw((unsigned)this->size, 0);
	}

	inline VertexBuffer<void>::~VertexBuffer()
	{
		delete[] this->data;

		_buffer->Release();

		this->data = nullptr;
		this->_buffer = nullptr;
	}
}
#endif