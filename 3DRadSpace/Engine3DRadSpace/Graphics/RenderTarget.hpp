#pragma once
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT RenderTarget : public Texture2D
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTarget;
#endif
	public:
		RenderTarget(GraphicsDevice *device, TextureFormat format = TextureFormat::R32G32B32A32_Float);
		RenderTarget(GraphicsDevice *device, unsigned x, unsigned y);

		RenderTarget(GraphicsDevice* device, unsigned x, unsigned y, TextureFormat format = TextureFormat::R32G32B32A32_Float);

		~RenderTarget() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}

