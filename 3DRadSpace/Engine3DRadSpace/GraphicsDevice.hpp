#pragma once
#include "Libs.hpp"
#include "VertexDeclarations.hpp"
#include "Viewport.hpp"
#include "VertexTopology.hpp"

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
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> screenTexture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mainRenderTarget;

		Engine3DRadSpace::Math::Point resoultion;
#endif
	public:
		GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);
		
		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&) = delete;

		void Clear(const Color& clearColor = {0.0f,0.0f,0.0f,1.0f});

		void SetViewport(const Viewport& viewport);
		void SetViewports(std::span<Viewport> viewports);

		template<Engine3DRadSpace::Graphics::VertexDecl V>
		void DrawVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer<V>* vertexBuffer);

		void SetShader(Engine3DRadSpace::Graphics::IShader *shader);
		void SetTopology(Graphics::VertexTopology topology);
		void DrawAuto();

		void Present();

		bool EnableVSync;

		Engine3DRadSpace::Math::Point Resolution();

		~GraphicsDevice();

		template<Graphics::VertexDecl V> friend class Graphics::VertexBuffer;
		friend class Graphics::IShader;
		friend class Graphics::Texture2D;
	};

	template<Engine3DRadSpace::Graphics::VertexDecl V>
	inline void GraphicsDevice::DrawVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer<V> *vertexBuffer)
	{
#ifdef _DX11
		int strides = sizeof(V);
		int offsets = 0;
		context->IASetVertexBuffers(0, 1, &vertexBuffer->buffer, &strides, &offsets);

		context->Draw(vertexBuffer->NumVerts(), 0);
#endif
	}
}
