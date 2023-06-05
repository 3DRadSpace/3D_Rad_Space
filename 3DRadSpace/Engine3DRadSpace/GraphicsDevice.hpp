#pragma once
#include "Libs.hpp"
#include "Viewport.hpp"
#include "Graphics/VertexDeclarations.hpp"
#include "Graphics/VertexTopology.hpp"
#include "Graphics/RasterizerState.hpp"
#include "Graphics/DepthStencilState.hpp"
#include "Graphics/BlendState.hpp"

namespace Engine3DRadSpace::Graphics
{
	template<VertexDecl V> class VertexBufferV;
	class VertexBuffer;
	class IndexBuffer;

	class IShader;
	class Texture2D;
	class DepthStencilBuffer;
	class SpriteBatch;
	class SamplerState;
	class RenderTarget;
	class BlendState;
}

namespace Engine3DRadSpace
{
	/// <summary>
	/// Graphics device represents a wrapped for GAPI(DirectX11) handles. GPU commands can be sent from here.
	/// </summary>
	class GraphicsDevice
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> _screenTexture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _mainRenderTarget;

		Engine3DRadSpace::Math::Point _resolution;

		std::unique_ptr<Graphics::DepthStencilBuffer> _stencilBuffer;
		std::unique_ptr<Graphics::BlendState> _blendState;
#endif
	public:
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;

		GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);
		
		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&) = delete;

		void Clear(const Color& clearColor = {0.0f,0.0f,0.0f,1.0f});

		void SetViewport(const Viewport& viewport);
		void SetViewports(std::span<Viewport> viewports);

		void SetNewDepthStencil(const Graphics::DepthStencilState& state);

		void SetRenderTarget(Graphics::RenderTarget *remderTarget);
		void SetRenderTargetAndDepth(Graphics::RenderTarget *renderTarget, Graphics::DepthStencilBuffer *depthBuffer);

		void DrawVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, unsigned startSlot = 0);
		void DrawVertexBufferWithindices(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, Engine3DRadSpace::Graphics::IndexBuffer* indexBuffer);

		void SetShader(Engine3DRadSpace::Graphics::IShader *shader);
		void SetTopology(Graphics::VertexTopology topology);
		void DrawAuto();
		void SetRasterizerState(const Graphics::RasterizerState *state);
		void Present();
		
		void SaveBackBufferToFile(const std::string &path);
		void SaveBackBufferToFile(const std::wstring &path);

		bool EnableVSync;

		Engine3DRadSpace::Math::Point Resolution();

		~GraphicsDevice();

		template<Graphics::VertexDecl V> friend class Graphics::VertexBufferV;

		friend class Graphics::VertexBuffer;
		friend class Graphics::IndexBuffer;
		friend class Graphics::IShader;
		friend class Graphics::Texture2D;
		friend class Graphics::RasterizerState;
		friend class Graphics::DepthStencilBuffer;
		friend class Graphics::SamplerState;
		friend class Graphics::SpriteBatch;
		friend class Graphics::DepthStencilBuffer;
	};
}
