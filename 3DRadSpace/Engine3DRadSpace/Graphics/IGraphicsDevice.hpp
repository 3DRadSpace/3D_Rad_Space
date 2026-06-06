#pragma once
#include "../Math/Point.hpp"
#include "../Math/Color.hpp"
#include "Viewport.hpp"
#include "VertexTopology.hpp"
#include "PixelFormat.hpp"
#include "BufferUsage.hpp"
#include "RenderTargetBlendState.hpp"
#include "DepthWriteMask.hpp"
#include "ComparisonFunction.hpp"
#include "FaceOperation.hpp"
#include "VertexDeclarations.hpp"
#include "../Core/IService.hpp"
#include "TextureFilter.hpp"
#include "TextureAddressMode.hpp"
#include "RasterizerFillMode.hpp"
#include "RasterizerCullMode.hpp"
#include "IVertexBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture1D;
	class ITexture2D;
	class ITexture3D;
	class ITextureCube;
	class IRenderTarget;
	class IDepthStencilBuffer;
	class IVertexBuffer;
	class IIndexBuffer;
	class IShader;
	class IRasterizerState;
	class IDepthStencilState;
	class IBlendState;
	class ISamplerState;
	class IShaderCompiler;
	class IGraphicsCommandList;

	class E3DRSP_GRAPHICS_EXPORT IGraphicsDevice : public IService
	{
	protected:
		IGraphicsDevice() = default;

		IGraphicsDevice(const IGraphicsDevice&) = delete;
		IGraphicsDevice& operator=(const IGraphicsDevice&) = delete;

		IGraphicsDevice(IGraphicsDevice&&) noexcept = default;
		IGraphicsDevice& operator=(IGraphicsDevice&&) noexcept = default;
	public:
		bool EnableVSync = true;

		virtual std::string_view BackendName() const noexcept = 0;

		/// <summary>
		/// Gets the depth stencil buffer that's currently created.
		/// </summary>
		/// <returns>An copy of the depth stencil state.</returns>
		virtual std::unique_ptr<IDepthStencilState> GetDepthStencilState() = 0;
		virtual std::unique_ptr<IRasterizerState> GetRasterizerState() = 0;

		virtual Math::Point Resolution() const noexcept = 0;

		virtual IRenderTarget* GetBackBuffer() const noexcept = 0;
		virtual ITexture2D *GetBackBufferTexture() const noexcept = 0;
		virtual IDepthStencilBuffer& GetDepthBuffer() = 0;

		virtual std::unique_ptr<IBlendState> CreateBlendState(
			bool alphaCoverage, 
			bool indepedentBlend,
			std::array<RenderTargetBlendState, 8> renderTargetBlendStates
		) = 0;

		virtual std::unique_ptr<IBlendState> CreateBlendState_Opaque() = 0;
		virtual std::unique_ptr<IBlendState> CreateBlendState_AlphaBlend() = 0;
		virtual std::unique_ptr<IBlendState> CreateBlendState_Additive() = 0;
		virtual std::unique_ptr<IBlendState> CreateBlendState_NonPremultiplied() = 0;

		virtual std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y
		) = 0;

		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState(
			bool EnableDepth, 
			DepthWriteMask Mask, 
			ComparisonFunction Function,
			bool EnableStencil,
			uint8_t ReadMask,
			uint8_t WriteMask,
			FaceOperation FrontFace,
			FaceOperation BackFace
		) = 0;

		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthDefault() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthNone() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthRead() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReverseZ() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReadReverseZ() = 0;

		virtual IShaderCompiler* ShaderCompiler() = 0;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		virtual ITexture2D* WhiteBlank() = 0;

		virtual IVertexBuffer* GetScreenQuad() const noexcept = 0;

		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) = 0;
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) = 0;

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
		) = 0;

		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullNone() = 0;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullClockwise() = 0;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullCounterClockwise() = 0;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_Wireframe() = 0;

		virtual std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState() = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState(
			TextureFilter filter,
			TextureAddressMode addressU,
			TextureAddressMode addressV,
			TextureAddressMode addressW,
			float mipLODBias,
			unsigned maxAnisotropy,
			ComparisonFunction comparisonFunc,
			const Math::Color &borderColor,
			float minLOD,
			float maxLOD
		) = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearClamp() = 0;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearWrap() = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointClamp() = 0;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointWrap() = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicClamp() = 0;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicWrap() = 0;

		virtual std::unique_ptr<ITexture1D> CreateTexture1D(
			size_t numElements,
			PixelFormat format
		) = 0;

		virtual std::unique_ptr<ITexture1D> CreateTexture1D(std::span<Math::Color> colors) = 0;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(
			void* data,
			size_t x,
			size_t y,
			PixelFormat format,
			BufferUsage usage
		) = 0;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(const std::filesystem::path& path) = 0;

		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(
			const void* data,
			size_t structSize,
			size_t numVertices,
			BufferUsage usage
		) = 0;

		virtual std::unique_ptr<ITextureCube> CreateTextureCube(const std::filesystem::path& path) = 0;
		virtual std::unique_ptr<ITextureCube> CreateTextureCube(std::array<ITexture2D*, 6> cubeMap) = 0;
		
		virtual std::unique_ptr<ITexture3D> CreateTexture3D(std::span<ITexture2D*> textures) = 0;

		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(std::span<const V> vertices, BufferUsage usage)
		{
			return CreateVertexBuffer(&vertices[0], sizeof(V), vertices.size(), usage);
		}

		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(std::span<V> vertices, BufferUsage usage)
		{
			return CreateVertexBuffer(const_cast<const V*>(&vertices[0]), sizeof(V), vertices.size(), usage);
		}

		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(size_t numVertices, BufferUsage usage)
		{
			return CreateVertexBuffer(nullptr, sizeof(V), numVertices, usage);
		}

		virtual std::unique_ptr<IGraphicsCommandList> CreateCommandList() = 0;
		virtual IGraphicsCommandList* ImmediateContext() = 0;

		virtual void* NativeHandle() const noexcept = 0;

		virtual ~IGraphicsDevice() override = default;
	};
}