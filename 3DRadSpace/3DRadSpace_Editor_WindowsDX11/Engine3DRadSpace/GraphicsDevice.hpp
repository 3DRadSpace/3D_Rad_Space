#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Graphics device represents a wrapped for GAPI(DirectX or Vulkan) handles. GPU commands can be sent from here.
	/// </summary>
	class GraphicsDevice
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
#endif
	public:
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);
		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&) = delete;

		~GraphicsDevice();
	};
}
