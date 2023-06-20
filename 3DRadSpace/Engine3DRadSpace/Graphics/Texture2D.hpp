#pragma once
#include "../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Texture2D
	{
		unsigned _width;
		unsigned _height;
	protected:
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _resourceView;
		GraphicsDevice *_device;
#endif

		void _retrieveSize();

		Texture2D(GraphicsDevice *device, unsigned x, unsigned y, bool bindRenderTarget);
		Texture2D(GraphicsDevice *device, bool bindRenderTarget = false);
	public:
		Texture2D(GraphicsDevice* device, const std::string &fileName);
		Texture2D(GraphicsDevice* device, const std::wstring &filename);

		Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y);
		Texture2D(GraphicsDevice *device, void* colors, unsigned x, unsigned y);
		Texture2D(GraphicsDevice *device, const uint8_t* imageBuffer, size_t size);
		Texture2D(GraphicsDevice *device, unsigned x, unsigned y);

		Texture2D(Texture2D &) = delete;
		Texture2D(Texture2D &&txt) noexcept = default;

		void SetColors(Color** colors, unsigned x, unsigned y);

		void SaveToFile(const std::string &path);

		unsigned Width();
		unsigned Height();

		friend class Engine3DRadSpace::GraphicsDevice;
		friend class IVertexShader;
		friend class IPixelShader;
		friend class IHullShader;
		friend class IDomainShader;
		friend class IGeometryShader;
	};
}

