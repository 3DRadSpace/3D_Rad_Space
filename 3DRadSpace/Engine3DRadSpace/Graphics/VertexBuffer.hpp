#pragma once
#include "../GraphicsDevice.hpp"
#include "VertexDeclarations.hpp"
#include "../Logging/Error.hpp"
#include "IShader.hpp"

namespace Engine3DRadSpace
{
	class GraphicsDevice;
	namespace Graphics
	{
		enum class BufferUsage : unsigned int
		{
			ReadWriteGPU,
			ReadOnlyGPU,
			ReadOnlyGPU_WriteOnlyCPU,
			Staging,
		};

		class VertexBuffer
		{
#ifdef  _DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
			GraphicsDevice* _device;

			size_t _numVerts;
			size_t _structSize;
#endif //  _DX11
		public:
			VertexBuffer(
				_In_ GraphicsDevice* device, 
				_In_reads_bytes_(p_structSize * numVertices) const void* data, 
				size_t p_structSize,
				size_t numVertices, 
				BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU
			);

			VertexBuffer(VertexBuffer &) = delete;
			VertexBuffer(VertexBuffer &&) noexcept = default;

			VertexBuffer &operator=(VertexBuffer &) = delete;
			VertexBuffer &operator=(VertexBuffer &&) noexcept = default;

			void SetData(void* data, size_t dataSize);
			void Set();
			void Draw(unsigned startIndex = 0);

			size_t TotalSize();
			size_t StructSize();
			size_t NumVertices();

			virtual ~VertexBuffer() = default;

			friend class ::Engine3DRadSpace::GraphicsDevice;
			friend class ModelMeshPart;
		};

		template<VertexDecl V>
		class VertexBufferV : public VertexBuffer
		{
		public:
			VertexBufferV( _In_ GraphicsDevice* device, _In_ std::span<V> data, BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
			void SetData(std::span<V> data);

			friend class ::Engine3DRadSpace::GraphicsDevice;
		};

		template<VertexDecl V>
		VertexBufferV<V>::VertexBufferV(_In_ GraphicsDevice* device, _In_ std::span<V> data, BufferUsage usage):
			VertexBuffer(device, &data[0], sizeof(V), data.size(), usage)
		{
		}

		template<VertexDecl V>
		inline void VertexBufferV<V>::SetData(std::span<V> data)
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