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
			Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
			GraphicsDevice *_device;

			size_t bufferSize;
#endif //  _DX11
		public:
			VertexBuffer(_In_ GraphicsDevice *device, _In_ const void *data, size_t size, BufferUsage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

			void SetData(void *data, size_t size);

			friend class Engine3DRadSpace::GraphicsDevice;
		};

		template<VertexDecl V>
		class VertexBuffer
		{
#ifdef  _DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
			GraphicsDevice *_device;
			
			size_t bufferSize;
#endif //  _DX11
		public:
			VertexBuffer( _In_ GraphicsDevice* device, _In_ std::span<V> data, IShader* shader = nullptr, BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

			void SetData(std::span<V> data);

			friend class Engine3DRadSpace::GraphicsDevice;
		};

		template<VertexDecl V>
		inline VertexBuffer<V>::VertexBuffer(GraphicsDevice* device, std::span<V> data, IShader *shader, BufferUsage usage):
			_device(device),
			bufferSize(data.size_bytes()) 
		{
#ifdef _DX11
			D3D11_BUFFER_DESC vertexBuffDesc{};
			vertexBuffDesc.ByteWidth = bufferSize;
			vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			vertexBuffDesc.BindFlags = static_cast<UINT>(usage);

			D3D11_SUBRESOURCE_DATA resource{};
			resource.pSysMem = &(data.begin()[0]);

			HRESULT r = device->_device->CreateBuffer(&vertexBuffDesc, &resource, _buffer.GetAddressOf());
			Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create a vertex buffer!");
#endif
		}

		template<VertexDecl V>
		inline void VertexBuffer<V>::SetData(std::span<V> data)
		{
#ifdef _DX11
			D3D11_MAPPED_SUBRESOURCE resource{};
			HRESULT r = _device->_context->Map(_buffer, 0, D3D11_MAP_WRITE, 0, &resource);
			Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to map a vertex buffer that cannot be written by the CPU.");
			
			memcpy_s(resource.pData, data.size_bytes(), &data[0], data.size_bytes());

			_device->_context->Unmap(_buffer, 0);
			Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to unmap a vertex buffer object when writing data.");
#endif
		}
	}
}