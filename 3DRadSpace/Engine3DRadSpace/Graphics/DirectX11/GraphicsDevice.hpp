#pragma once
#include "DirectX11.h"
#include "../../Core/Libs.hpp"
#include "../Viewport.hpp"
#include "../VertexDeclarations.hpp"
#include "../VertexTopology.hpp"
#include "RasterizerState.hpp"
#include "DepthStencilState.hpp"
#include "DepthStencilBuffer.hpp"
#include "BlendState.hpp"
#include "../IGraphicsDevice.hpp"
#include "../GraphicsDeviceCreationOptions.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class VertexBuffer;
	class IndexBuffer;

	class Texture1D;
	class Texture2D;
	class Texture3D;
	class TextureCube;
	class RenderTarget;
	class DepthStencilBuffer;
	class DepthStencilState;
	class SpriteBatch;
	class SamplerState;
	class RenderTarget;
	class BlendState;

	class ShaderBase;
	class VertexShader;
	class HullShader;
	class DomainShader;
	class GeometryShader;
	class FragmentShader;

	class GraphicsCommandList;
	class ShaderCompiler;
	class DeferredCommandList;

	/// <summary>
	/// DirectX11 RHI (Rendering Hardware Interface)
	/// </summary>
	class E3DRSP_GRAPHICS_DX11_EXPORT GraphicsDevice final : public IGraphicsDevice
	{
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;

		std::unique_ptr<DirectX11::RenderTarget> _backbufferRT;

		Math::Point _resolution;
		bool _fullscreen = false;
		bool _hasHDR = false;

		std::unique_ptr<DepthStencilBuffer> _stencilBuffer;
		std::unique_ptr<DepthStencilState> _stencilState;
		std::unique_ptr<BlendState> _blendState;

		///Used for rendering post effects
		std::unique_ptr<VertexBuffer> _screenQuad;
		std::unique_ptr<ITexture2D> _white2x2;

		std::unique_ptr<GraphicsCommandList> _immediateContext;
		std::unique_ptr<DirectX11::ShaderCompiler> _compiler;

		std::string _backendName = "DirectX11";

		void _createBackBuffer();
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(
			void* nativeWindowHandle,
			size_t width = 800, 
			size_t height = 600,
			GraphicsDeviceCreationOptions opt = GraphicsDeviceCreationOptions::Unspecified
		);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		std::string_view BackendName() const noexcept override;

		/// <summary>
		/// Returns the backbuffer width and height.
		/// </summary>
		/// <returns></returns>
		Math::Point Resolution() const noexcept override;

		IRenderTarget* GetBackBuffer() const noexcept override;
		ITexture2D *GetBackBufferTexture() const noexcept override;
		IDepthStencilBuffer& GetDepthBuffer() override;

		std::unique_ptr<IDepthStencilState> GetDepthStencilState() override;
		std::unique_ptr<IRasterizerState> GetRasterizerState() override;

		//Graphics::PixelFormat BackBufferFormat() const noexcept;

		std::unique_ptr<IBlendState> CreateBlendState(
			bool alphaCoverage, 
			bool indepedentBlend,
			std::array<RenderTargetBlendState, 8> renderTargetBlendStates
		) override;

		std::unique_ptr<IBlendState> CreateBlendState_Opaque() override;
		std::unique_ptr<IBlendState> CreateBlendState_AlphaBlend() override;
		std::unique_ptr<IBlendState> CreateBlendState_Additive() override;
		std::unique_ptr<IBlendState> CreateBlendState_NonPremultiplied() override;

		std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y
		) override;

		std::unique_ptr<IDepthStencilState> CreateDepthStencilState(
			bool EnableDepth, 
			DepthWriteMask Mask, 
			ComparisonFunction Function,
			bool EnableStencil,
			uint8_t ReadMask,
			uint8_t WriteMask,
			FaceOperation FrontFace,
			FaceOperation BackFace
		) override;

		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthDefault() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthNone() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthRead() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReverseZ() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReadReverseZ() override;

		virtual IShaderCompiler* ShaderCompiler() override;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		virtual ITexture2D* WhiteBlank() override;

		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) override;
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) override;

		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState(
			RasterizerFillMode filling = RasterizerFillMode::Solid,
			RasterizerCullMode culling = RasterizerCullMode::CullBack,
			bool switchFrontBack = false,
			int depthBias = 0,
			float depthBiasClamp = 0,
			float slopeScaleDepthBias = 0,
			bool depthClip = false,
			bool scissor = false,
			bool multisample = false,
			bool aaLine = false
		) override;

		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullNone() override;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullClockwise() override;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullCounterClockwise() override;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_Wireframe() override;

		virtual std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState() override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState(
			TextureFilter filter,
			TextureAddressMode addressU,
			TextureAddressMode addressV,
			TextureAddressMode addressW,
			float mipLODBias,
			unsigned maxAnisotropy,
			ComparisonFunction comparisonFunc,
			const Math::Color& borderColor,
			float minLOD,
			float maxLOD
		) override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearClamp() override;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearWrap() override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointClamp() override;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointWrap() override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicClamp() override;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicWrap() override;

		virtual std::unique_ptr<ITexture1D> CreateTexture1D(
			size_t numElements,
			PixelFormat format
		) override;

		virtual std::unique_ptr<ITexture1D> CreateTexture1D(std::span<Math::Color> colors) override;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(
			void* data,
			size_t x,
			size_t y,
			PixelFormat format,
			BufferUsage usage
		) override;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(const std::filesystem::path& path) override;

		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(
			const void* data,
			size_t structSize,
			size_t numVertices,
			BufferUsage usage
		) override;

		virtual std::unique_ptr<ITextureCube> CreateTextureCube(std::array<ITexture2D*, 6> faces) override;
		virtual std::unique_ptr<ITextureCube> CreateTextureCube(const std::filesystem::path& path) override;

		virtual std::unique_ptr<ITexture3D> CreateTexture3D(std::span<ITexture2D*> textures) override;

		virtual std::unique_ptr<IGraphicsCommandList> CreateCommandList() override;
		virtual IGraphicsCommandList* ImmediateContext() override;

		IVertexBuffer* GetScreenQuad() const noexcept override;

		void* NativeHandle() const noexcept override;

		~GraphicsDevice() override;

		friend class VertexBuffer;
		friend class IndexBuffer;
		friend class Texture1D;
		friend class Texture2D;
		friend class Texture3D;
		friend class TextureCube;
		friend class RenderTarget;
		friend class RasterizerState;
		friend class DepthStencilState;
		friend class SamplerState;
		friend class SpriteBatch;
		friend class DepthStencilBuffer;
		friend class BlendState;

		friend class ShaderBase;
		friend class VertexShader;
		friend class HullShader;
		friend class DomainShader;
		friend class GeometryShader;
		friend class FragmentShader;

		friend class GraphicsCommandList;
		friend class DeferredCommandList;
	};
}
