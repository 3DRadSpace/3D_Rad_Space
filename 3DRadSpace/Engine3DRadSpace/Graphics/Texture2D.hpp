#pragma once
#include "../GraphicsDevice.hpp"
#include "PixelFormat.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT Texture2D
	{
		unsigned _width;
		unsigned _height;

		void _debugInfoTX2D();
		void _debugInfoRT();
        Texture2D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& resource);
        Texture2D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture);
	protected:
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _resourceView;
		GraphicsDevice *_device;

        DXGI_FORMAT _getTextureFormat(PixelFormat format);
#endif
		void _retrieveSize();

		Texture2D(GraphicsDevice *device, unsigned x, unsigned y, bool bindRenderTarget, PixelFormat format = PixelFormat::R32G32B32A32_Float);
		Texture2D(GraphicsDevice *device, bool bindRenderTarget = false, PixelFormat format = PixelFormat::R32G32B32A32_Float);
	public:
		explicit Texture2D(GraphicsDevice* device, const std::string &fileName);
		explicit Texture2D(GraphicsDevice* device, const std::wstring &filename);

		explicit Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y);
		explicit Texture2D(GraphicsDevice *device, Color* colors, unsigned x, unsigned y);
		explicit Texture2D(GraphicsDevice* device, void* buffer, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);
		explicit Texture2D(GraphicsDevice *device, const uint8_t* imageBuffer, size_t size);
		explicit Texture2D(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);

		Texture2D(Texture2D &) = delete;
		Texture2D(Texture2D &&txt) noexcept = default;

		void SetColors(Color** colors, unsigned x, unsigned y);
		void Resize(unsigned newX, unsigned newY);

		void SaveToFile(const std::string &path);

		unsigned Width();
		unsigned Height();

        static Texture2D CreateStaging(Texture2D* texture);
        Texture2D Clone();

		virtual ~Texture2D() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
		friend class IVertexShader;
		friend class IPixelShader;
		friend class IHullShader;
		friend class IDomainShader;
		friend class IGeometryShader;
	};
}

