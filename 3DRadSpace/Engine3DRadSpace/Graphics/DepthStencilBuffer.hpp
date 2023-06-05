#pragma once
#include "../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DepthStencilBuffer
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _stencilState;
#endif
		GraphicsDevice *_device;
	public:
		explicit DepthStencilBuffer(GraphicsDevice* device);

		DepthStencilBuffer(DepthStencilBuffer &) = delete;
		DepthStencilBuffer(DepthStencilBuffer &&buff) noexcept;

		DepthStencilBuffer &operator=(DepthStencilBuffer &) = delete;
		DepthStencilBuffer &operator=(DepthStencilBuffer &&buff) noexcept;

		friend class GraphicsDevice;
	};
}
