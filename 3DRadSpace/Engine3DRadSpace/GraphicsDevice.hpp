#pragma once
#include "Libs.hpp"
#include "VertexDeclarations.hpp"
#include "Viewport.hpp"
#include "VertexTopology.hpp"
#include "RasterizerState.hpp"
#include "DepthStencilState.hpp"

#ifdef  _DX11
#pragma comment(lib,"d3d11.lib")
#endif //  _DX11

namespace Engine3DRadSpace::Graphics
{
	template<VertexDecl V> class VertexBufferV;
	class VertexBuffer;
	class IndexBuffer;

	class IShader;
	class Texture2D;
	class DepthStencilBuffer;
}

namespace Engine3DRadSpace
{
	/// <summary>
	/// Graphics device represents a wrapped for GAPI(DirectX11) handles. GPU commands can be sent from here.
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

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthView;

		void createDepthStencil();
		void createDepthTexture();
		void createDepthView();
#endif
	public:
		GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);
		
		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&) = delete;

		void Clear(const Color& clearColor = {0.0f,0.0f,0.0f,1.0f});

		void SetViewport(const Viewport& viewport);
		void SetViewports(std::span<Viewport> viewports);

		void SetNewDepthStencil(const DepthStencilState& state);

		void DrawVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, unsigned startSlot = 0);
		void DrawVertexBufferWithindices(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, Engine3DRadSpace::Graphics::IndexBuffer* indexBuffer);

		void SetShader(Engine3DRadSpace::Graphics::IShader *shader);
		void SetTopology(Graphics::VertexTopology topology);
		void DrawAuto();
		void SetRasterizerState(const RasterizerState *state);
		void Present();

		bool EnableVSync;

		Engine3DRadSpace::Math::Point Resolution();

		~GraphicsDevice();

		template<Graphics::VertexDecl V> friend class Graphics::VertexBufferV;
		friend class Graphics::VertexBuffer;
		friend class Graphics::IndexBuffer;
		friend class Graphics::IShader;
		friend class Graphics::Texture2D;
		friend class RasterizerState;
		friend class DepthStencilBuffer;
	};
}
