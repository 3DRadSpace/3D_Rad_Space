#pragma once
#include "../GraphicsDevice.hpp"
#include "DepthStencilState.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DepthStencilBuffer
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthTexture;
#endif
		GraphicsDevice *_device;
		void _createDepthTexture();
	public:
		explicit DepthStencilBuffer(GraphicsDevice* device);

		DepthStencilBuffer(DepthStencilBuffer &) = delete;
		DepthStencilBuffer(DepthStencilBuffer &&buff) noexcept = default;

		DepthStencilBuffer &operator=(DepthStencilBuffer &) = delete;
		DepthStencilBuffer &operator=(DepthStencilBuffer &&buff) noexcept = default;

		friend class GraphicsDevice;
	};
}
