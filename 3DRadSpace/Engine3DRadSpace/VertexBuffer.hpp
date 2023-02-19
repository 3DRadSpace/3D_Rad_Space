#pragma once
#include "GraphicsDevice.hpp"
#include "VertexDeclarations.hpp"
#include "Error.hpp"
#include "IShader.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		enum class BufferUsage : unsigned int
		{
			ReadWriteGPU,
			ReadOnlyGPU,
			ReadOnlyGPU_WriteOnlyCPU,
			Staging,
		};

		template<>
		class VertexBuffer<UnspecifiedVertexDecl>
		{
#ifdef  _DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
			GraphicsDevice *device;

			size_t bufferSize;
			size_t numVerts;
			size_t structSize;
#endif //  _DX11
		public:
			VertexBuffer(_In_ GraphicsDevice *device, _In_ const void *data, size_t p_structSize,size_t numVerticies, BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

			void SetData(void *data, size_t size);
			void Set();

			friend class Engine3DRadSpace::GraphicsDevice;
		};

		template<VertexDecl V>
		class VertexBuffer
		{
#ifdef  _DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
			GraphicsDevice *device;
			
			size_t bufferSize;
			size_t numVerts;
#endif //  _DX11
		public:
			VertexBuffer( _In_ GraphicsDevice* device, _In_ std::span<V> data, IShader* shader = nullptr, BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

			void SetData(std::span<V> data);
			void Set();
			void Draw(unsigned startIndex = 0);
			void SetAndDraw(unsigned startIndex = 0);

			size_t TotalSize();
			size_t StructSize();
			unsigned NumVerticies();

			friend class Engine3DRadSpace::GraphicsDevice;
		};

		template<VertexDecl V>
		inline VertexBuffer<V>::VertexBuffer(GraphicsDevice* device, std::span<V> data, IShader *shader, BufferUsage usage):
			device(device),
			bufferSize(data.size_bytes()),
			numVerts(data.size())
		{
#ifdef _DX11
			D3D11_BUFFER_DESC vertexBuffDesc{};
			vertexBuffDesc.ByteWidth = (UINT)bufferSize;
			vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBuffDesc.CPUAccessFlags = 0;
			vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBuffDesc.StructureByteStride = sizeof(V);

			D3D11_SUBRESOURCE_DATA resource{};
			resource.pSysMem = &(data.begin()[0]);

			HRESULT r = device->device->CreateBuffer(&vertexBuffDesc, &resource, &buffer);
			Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create a vertex buffer!");
#endif
		}

		template<VertexDecl V>
		inline void VertexBuffer<V>::SetData(std::span<V> data)
		{
#ifdef _DX11
			D3D11_MAPPED_SUBRESOURCE resource{};
			HRESULT r = device->context->Map(buffer, 0, D3D11_MAP_WRITE, 0, &resource);
			Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to map a vertex buffer that cannot be written by the CPU.");
			
			memcpy_s(resource.pData, data.size_bytes(), &data[0], data.size_bytes());

			device->context->Unmap(buffer, 0);
			Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to unmap a vertex buffer object when writing data.");
#endif
		}

		template<Engine3DRadSpace::Graphics::VertexDecl V>
		inline void VertexBuffer<V>::Set()
		{
#ifdef _DX11
			unsigned strides = sizeof(V);
			unsigned offsets = 0;
			this->device->context->IASetVertexBuffers(0, 1, this->buffer.GetAddressOf(), &strides, &offsets);
#endif
		}

		template<VertexDecl V>
		inline void VertexBuffer<V>::Draw(unsigned startIndex)
		{
#ifdef  _DX11
			this->device->context->Draw((UINT)this->numVerts, startIndex);
#endif //  _DX11
		}

		template<VertexDecl V>
		inline void VertexBuffer<V>::SetAndDraw(unsigned startIndex)
		{
			Set();
			Draw(startIndex);
		}

		template<VertexDecl V>
		inline size_t VertexBuffer<V>::TotalSize()
		{
			return this->bufferSize;
		}

		template<VertexDecl V>
		inline unsigned VertexBuffer<V>::NumVerticies()
		{
			return this->numVerts;
		}

		template<VertexDecl V>
		inline size_t VertexBuffer<V>::StructSize()
		{
			return sizeof(V);
		}
	}
}