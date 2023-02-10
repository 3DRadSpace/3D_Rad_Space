#pragma once
#include "Libs.hpp"
#include "VertexDeclarations.hpp"
#include "Viewport.hpp"

#ifdef  _DX11
#pragma comment(lib,"d3d11.lib")
#endif //  _DX11

namespace Engine3DRadSpace::Graphics
{
	template<VertexDecl V> class VertexBuffer;
	class IShader;
	class Texture2D;
}

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
		GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);
		//GraphicsDevice(GraphicsDevice&) = delete;
		//GraphicsDevice(GraphicsDevice&&) = delete;
		//GraphicsDevice& operator=(GraphicsDevice&) = delete;

		void Clear(const Color& clearColor = {0.0f,0.0f,0.0f,1.0f});

		void SetViewport(const Viewport& viewport);
		void SetViewports(std::span<Viewport> viewports);

		template<Engine3DRadSpace::Graphics::VertexDecl V>
		void SetVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer<V>* vertexBuffer);

		void SetShader(Engine3DRadSpace::Graphics::IShader *shader);

		void Present();

		bool EnableVSync;

		~GraphicsDevice();

		template<Graphics::VertexDecl V> friend class Graphics::VertexBuffer;
		friend class Graphics::IShader;
		friend class Graphics::Texture2D;
	};

	template<Engine3DRadSpace::Graphics::VertexDecl V>
	inline void GraphicsDevice::SetVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer<V> *vertexBuffer)
	{
#ifdef _DX11
		int strides = 0;
		int offsets = 0;
		_context->IASetVertexBuffers(0, 1, &vertexBuffer->_buffer, &strides, &offsets);
#endif
	}
}
