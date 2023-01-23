#pragma once
#include "Libs.hpp"
#include "Color.hpp"
#include "Viewport.hpp"

#ifdef  _DX11
#pragma comment(lib,"d3d11.lib")
#endif //  _DX11


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

		Microsoft::WRL::ComPtr<ID3D11Texture2D> _screenTexture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _mainRenderTarget;
#endif
	public:
		//GraphicsDevice(unsigned width = 800, unsigned height = 600);
		GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);
		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&) = delete;

		void Clear(const Color& clearColor = {0.0f,0.0f,0.0f,1.0f});

		void SetViewport(const Viewport& viewport);
		void SetViewports(const Viewport viewports[], unsigned numViewports);

		void Present();

		bool EnableVSync;

		~GraphicsDevice();
	};
}
