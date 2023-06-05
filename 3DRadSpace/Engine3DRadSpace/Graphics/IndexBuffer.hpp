#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace
{
	class GraphicsDevice;
	namespace Graphics
	{
		class IndexBuffer
		{
#ifdef _DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;
#endif
			GraphicsDevice* _device;

		public:
			IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices);
			IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices);

			void Set(unsigned index = 0);
			void SetData(std::span<unsigned> newindices);

			friend class GraphicsDevice;
		};
	}
}

