#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	class GraphicsDevice;
	namespace Graphics
	{
		class IndexBuffer
		{
			Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
			GraphicsDevice* device;

		public:
			IndexBuffer(GraphicsDevice* device, std::span<unsigned> indicies);
			IndexBuffer(GraphicsDevice* device, unsigned* indicies, size_t numIndicies);

			void Set(std::span<unsigned> newIndicies);

			friend class GraphicsDevice;
		};
	}
}

