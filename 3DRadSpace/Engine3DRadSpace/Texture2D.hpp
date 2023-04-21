#pragma once
#include "GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Texture2D
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resourceView;
#endif
	public:
		Texture2D(GraphicsDevice* device,const char *fileName);
		Texture2D(GraphicsDevice* device, const wchar_t* filename);

		Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y);
		Texture2D(GraphicsDevice* device, void* colors, unsigned x, unsigned y);
		Texture2D(GraphicsDevice* device, const uint8_t* imageBuffer, size_t size);

		void SetColors(Color** colors, unsigned x, unsigned y);

		friend class GraphicsDevice;
		friend class IShader;
	};
}

