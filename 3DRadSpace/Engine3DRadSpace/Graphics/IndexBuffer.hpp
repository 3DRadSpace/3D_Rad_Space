#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace
{
	class GraphicsDevice;
	namespace Graphics
	{
		class DLLEXPORT IndexBuffer
		{
#ifdef _DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;
#endif
			GraphicsDevice* _device;

			unsigned _numIndices;

			void _debugInfo();
		public:
			IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices);
			IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices);

			IndexBuffer(IndexBuffer &) = delete;
			IndexBuffer(IndexBuffer &&) noexcept = default;

			IndexBuffer &operator=(IndexBuffer &) = delete;
			IndexBuffer &operator=(IndexBuffer &&) noexcept = default;

			void Set(unsigned index = 0);
			void SetData(std::span<unsigned> newindices);

			unsigned NumIndices() const;

			~IndexBuffer() = default;

			friend class GraphicsDevice;
			friend class ModelMeshPart;
		};
	}
}

