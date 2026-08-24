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
		/// Gets the depth stencil buffer that's currently set.
		/// </summary>
		/// <returns>An copy of the depth stencil state.</returns>
		virtual std::unique_ptr<IDepthStencilState> GetDepthStencilState() = 0;
		/// <summary>
		/// Gets the current blend state.
		/// </summary>
		/// <returns>Copy of the rasterizer state.</returns>
		virtual std::unique_ptr<IRasterizerState> GetRasterizerState() = 0;

		/// <summary>
		///	Gets the backbuffer size.
		/// </summary>
		/// <returns>Resolution of the backbuffer in pixels.</returns>
		virtual Math::Point Resolution() const noexcept = 0;

		/// <summary>
		/// Gets the backbuffer render target view.
		/// </summary>
		virtual IRenderTarget* GetBackBuffer() const noexcept = 0;
		/// <summary>
		/// Gets the backbuffer texture.
		/// </summary>
		/// <returns>Pointer to the backbuffer texture.</returns>
		virtual ITexture2D *GetBackBufferTexture() const noexcept = 0;
		/// <summary>
		/// Gets the default depth stencil buffer.
		/// </summary>
		/// <returns>Reference to the default depth stencil buffer.</returns>
		virtual IDepthStencilBuffer& GetDepthBuffer() = 0;

		/// <summary>
		/// Creates a new blend state.
		/// </summary>
		/// <param name="alphaCoverage">Indicates whether alpha coverage is enabled.</param>
		/// <param name="indepedentBlend">Indicates whether independent blend is enabled.</param>
		/// <param name="renderTargetBlendStates">Array of render target blend states.</param>
		/// <returns>Unique pointer to the created blend state.</returns>
		virtual std::unique_ptr<IBlendState> CreateBlendState(
			bool alphaCoverage, 
			bool indepedentBlend,
			std::array<RenderTargetBlendState, 8> renderTargetBlendStates
		) = 0;

		/// <summary>
		///	Creates a new opaque blend state.
		/// </summary>
		/// <returns>Unique pointer to the created blend state.</returns>
		virtual std::unique_ptr<IBlendState> CreateBlendState_Opaque() = 0;
		/// <summary>
		/// Creates a new alpha blend state.
		/// </summary>
		/// <returns>Unique pointer to the created blend state.</returns>
		virtual std::unique_ptr<IBlendState> CreateBlendState_AlphaBlend() = 0;
		/// <summary>
		/// Creates a new additive blend state.
		/// </summary>
		/// <returns>Unique pointer to the created blend state.</returns>
		virtual std::unique_ptr<IBlendState> CreateBlendState_Additive() = 0;
		/// <summary>
		/// Creates a new non-premultiplied blend state.
		/// </summary>
		/// <returns>Unique pointer to the created blend state.</returns>
		virtual std::unique_ptr<IBlendState> CreateBlendState_NonPremultiplied() = 0;

		/// <summary>
		/// Creates a new depth stencil buffer with the specified dimensions.
		/// </summary>
		/// <param name="x">The width of the depth stencil buffer.</param>
		/// <param name="y">The height of the depth stencil buffer.</param>
		/// <returns>Unique pointer to the created depth stencil buffer.</returns>
		virtual std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y
		) = 0;

		/// <summary>
		/// Creates a new depth stencil state with the specified parameters.
		/// </summary>
		/// <param name="EnableDepth">Indicates whether depth testing is enabled.</param>
		/// <param name="Mask">Specifies the depth write mask.</param>
		/// <param name="Function">Specifies the depth comparison function.</param>
		/// <param name="EnableStencil">Indicates whether stencil testing is enabled.</param>
		/// <param name="ReadMask">Specifies the stencil read mask.</param>
		/// <param name="WriteMask">Specifies the stencil write mask.</param>
		/// <param name="FrontFace">Specifies the stencil operations for front-facing polygons.</param>
		/// <param name="BackFace">Specifies the stencil operations for back-facing polygons.</param>
		/// <returns>Unique pointer to the created depth stencil state.</returns>
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

		/// <summary>
		/// Creates a new default depth stencil state with depth testing enabled, depth writes enabled, and the comparison function set to less than or equal.
		/// </summary>
		/// <returns>Unique pointer to the created depth stencil state.</returns>
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthDefault() = 0;
		/// <summary>
		/// Creates a new depth stencil state with depth testing disabled and depth writes disabled.
		/// </summary>
		/// <returns>Unique pointer to the created depth stencil state.</returns>
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthNone() = 0;
		/// <summary>
		/// Creates a new depth stencil state with depth testing enabled, depth writes disabled, and the comparison function set to less than or equal.
		/// </summary>
		/// <returns>Unique pointer to the created depth stencil state.</returns>
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthRead() = 0;
		/// <summary>
		///	Creates a new depth stencil state with depth testing enabled, depth writes enabled, and the comparison function set to greater than or equal.
		/// </summary>
		/// <returns>Unique pointer to the created depth stencil state.</returns>
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReverseZ() = 0;
		/// <summary>
		/// Creates a new depth stencil state with depth testing enabled, depth writes disabled, and the comparison function set to greater than or equal.
		/// </summary>
		/// <returns>Unique pointer to the created depth stencil state.</returns>
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReadReverseZ() = 0;

		/// <summary>
		/// Gets the associated shader compiler class.
		/// </summary>
		/// <returns>Pointer to the shader compiler.</returns>
		virtual IShaderCompiler* ShaderCompiler() = 0;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		virtual ITexture2D* WhiteBlank() = 0;

		/// <summary>
		/// Gets an vertex buffer that covers the entire backbuffer.
		/// </summary>
		/// <returns>Vertex buffer reference</returns>
		virtual IVertexBuffer* GetScreenQuad() const noexcept = 0;

		/// <summary>
		/// Creates a new index buffer from the specified indices.
		/// </summary>
		/// <param name="indices">Span of indices</param>
		/// <returns>Unique pointer to the created index buffer</returns>
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) = 0;
		/// <summary>
		/// Creates a new index buffer with data not set.
		/// </summary>
		/// <param name="numIndices">Number of indices</param>
		/// <param name="usage">Buffer usage</param>
		/// <returns>Unique pointer to the created index buffer</returns>
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) = 0;

		/// <summary>
		/// Creates a new rasterizer state with the specified parameters.
		/// </summary>
		/// <param name="filling">Rasterizer fill mode</param>
		/// <param name="culling">Rasterizer cull mode</param>
		/// <param name="switchFrontBack">Whether to switch front and back faces</param>
		/// <param name="depthBias">Depth bias</param>
		/// <param name="depthBiasClamp">Depth bias clamp</param>
		/// <param name="slopeScaleDepthBias">Slope scale depth bias</param>
		/// <param name="depthClip">Whether to enable depth clipping</param>
		/// <param name="scissor">Whether to enable scissor testing</param>
		/// <param name="multisample">Whether to enable multisampling</param>
		/// <param name="aaLine">Whether to enable anti-aliased lines</param>
		/// <returns>Unique pointer to the created rasterizer state</returns>
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

		/// <summary>
		/// Creates a new rasterizer state with culling disabled.
		/// </summary>
		/// <returns>Unique pointer to the created rasterizer state</returns>
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullNone() = 0;
		/// <summary>
		/// Creates a new rasterizer state with clockwise culling.
		/// </summary>
		/// <returns>Unique pointer to the created rasterizer state</returns>
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullClockwise() = 0;
		/// <summary>
		/// Creates a new rasterizer state with counter-clockwise culling.
		/// </summary>
		/// <returns>Unique pointer to the created rasterizer state</returns>
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullCounterClockwise() = 0;
		/// <summary>
		/// Creates a new rasterizer state with wireframe fill mode.
		/// </summary>
		/// <returns>Unique pointer to the created rasterizer state</returns>
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_Wireframe() = 0;

		/// <summary>
		/// Creates a new render target with the specified dimensions and pixel format.
		/// </summary>
		/// <param name="x">Width of the render target</param>
		/// <param name="y">Height of the render target</param>
		/// <param name="format">Pixel format of the render target</param>
		/// <returns>Unique pointer to the created render target</returns>
		virtual std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) = 0;

		/// <summary>
		/// Creates a new texture sampler state with default parameters.
		/// </summary>
		/// <returns>Unique pointer to the created sampler state</returns>
		virtual std::unique_ptr<ISamplerState> CreateSamplerState() = 0;

		/// <summary>
		///	Creates a new texture sampler state with the specified parameters.
		/// </summary>
		/// <param name="filter">Texture filtering mode to use for minification, magnification, and mip-level sampling</param>
		/// <param name="addressU">Addressing mode for the U texture coordinate</param>
		/// <param name="addressV">Addressing mode for the V texture coordinate</param>
		/// <param name="addressW">Addressing mode for the W texture coordinate</param>
		/// <param name="mipLODBias">Offset applied to the calculated mipmap level</param>
		/// <param name="maxAnisotropy">Clamping value used when the filter is anisotropic</param>
		/// <param name="comparisonFunc">Comparison function used when sampling with a comparison filter</param>
		/// <param name="borderColor">Border color used when an address mode is set to Border</param>
		/// <param name="minLOD">Lower end of the mipmap range to clamp access to</param>
		/// <param name="maxLOD">Upper end of the mipmap range to clamp access to</param>
		/// <returns>Unique pointer to the created sampler state</returns>
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

		/// <summary>
		/// Creates a new sampler state using linear filtering with clamp addressing on all axes.
		/// </summary>
		/// <returns>Unique pointer to the created sampler state</returns>
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearClamp() = 0;
		/// <summary>
		/// Creates a new sampler state using linear filtering with wrap addressing on all axes.
		/// </summary>
		/// <returns>Unique pointer to the created sampler state</returns>
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearWrap() = 0;

		/// <summary>
		/// Creates a new sampler state using point filtering with clamp addressing on all axes.
		/// </summary>
		/// <returns>Unique pointer to the created sampler state</returns>
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointClamp() = 0;
		/// <summary>
		/// Creates a new sampler state using point filtering with wrap addressing on all axes.
		/// </summary>
		/// <returns>Unique pointer to the created sampler state</returns>
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointWrap() = 0;

		/// <summary>
		/// Creates a new sampler state using anisotropic filtering with clamp addressing on all axes.
		/// </summary>
		/// <returns>Unique pointer to the created sampler state</returns>
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicClamp() = 0;
		/// <summary>
		/// Creates a new sampler state using anisotropic filtering with wrap addressing on all axes.
		/// </summary>
		/// <returns>Unique pointer to the created sampler state</returns>
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicWrap() = 0;

		/// <summary>
		/// Creates a new 1D texture with the specified number of elements and pixel format.
		/// </summary>
		/// <param name="numElements">Number of elements (texels) in the texture</param>
		/// <param name="format">Pixel format of the texture</param>
		/// <returns>Unique pointer to the created 1D texture</returns>
		virtual std::unique_ptr<ITexture1D> CreateTexture1D(
			size_t numElements,
			PixelFormat format
		) = 0;

		/// <summary>
		/// Creates a new 1D texture initialized with the specified colors.
		/// </summary>
		/// <param name="colors">Span of colors used to initialize the texture</param>
		/// <returns>Unique pointer to the created 1D texture</returns>
		virtual std::unique_ptr<ITexture1D> CreateTexture1D(std::span<Math::Color> colors) = 0;

		/// <summary>
		/// Creates a new 2D texture with the specified dimensions, pixel format, and initial data.
		/// </summary>
		/// <param name="data">Pointer to the initial texture data, or nullptr to leave the texture uninitialized</param>
		/// <param name="x">Width of the texture</param>
		/// <param name="y">Height of the texture</param>
		/// <param name="format">Pixel format of the texture</param>
		/// <param name="usage">Buffer usage of the texture</param>
		/// <returns>Unique pointer to the created 2D texture</returns>
		virtual std::unique_ptr<ITexture2D> CreateTexture2D(
			void* data,
			size_t x,
			size_t y,
			PixelFormat format,
			BufferUsage usage
		) = 0;

		/// <summary>
		/// Creates a new 2D texture by loading it from an image file.
		/// </summary>
		/// <param name="path">Path to the image file</param>
		/// <returns>Unique pointer to the created 2D texture</returns>
		virtual std::unique_ptr<ITexture2D> CreateTexture2D(const std::filesystem::path& path) = 0;

		/// <summary>
		/// Creates a new vertex buffer from raw vertex data.
		/// </summary>
		/// <param name="data">Pointer to the initial vertex data, or nullptr to leave the buffer uninitialized</param>
		/// <param name="structSize">Size, in bytes, of a single vertex structure</param>
		/// <param name="numVertices">Number of vertices in the buffer</param>
		/// <param name="usage">Buffer usage of the vertex buffer</param>
		/// <returns>Unique pointer to the created vertex buffer</returns>
		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(
			const void* data,
			size_t structSize,
			size_t numVertices,
			BufferUsage usage
		) = 0;

		/// <summary>
		/// Creates a new cube texture by loading it from a file.
		/// </summary>
		/// <param name="path">Path to the cube map file</param>
		/// <returns>Unique pointer to the created cube texture</returns>
		virtual std::unique_ptr<ITextureCube> CreateTextureCube(const std::filesystem::path& path) = 0;
		/// <summary>
		/// Creates a new cube texture from six individual 2D textures, one for each face.
		/// </summary>
		/// <param name="cubeMap">Array of six 2D textures, in the order +X, -X, +Y, -Y, +Z, -Z</param>
		/// <returns>Unique pointer to the created cube texture</returns>
		virtual std::unique_ptr<ITextureCube> CreateTextureCube(std::array<ITexture2D*, 6> cubeMap) = 0;

		/// <summary>
		/// Creates a new 3D texture from a span of 2D textures, each representing a depth slice.
		/// </summary>
		/// <param name="textures">Span of 2D textures used as depth slices</param>
		/// <returns>Unique pointer to the created 3D texture</returns>
		virtual std::unique_ptr<ITexture3D> CreateTexture3D(std::span<ITexture2D*> textures) = 0;

		/// <summary>
		/// Creates a new vertex buffer from a span of strongly-typed, const vertices.
		/// </summary>
		/// <typeparam name="V">Vertex declaration type</typeparam>
		/// <param name="vertices">Span of vertices used to initialize the buffer</param>
		/// <param name="usage">Buffer usage of the vertex buffer</param>
		/// <returns>Unique pointer to the created vertex buffer</returns>
		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(std::span<const V> vertices, BufferUsage usage)
		{
			return CreateVertexBuffer(&vertices[0], sizeof(V), vertices.size(), usage);
		}

		/// <summary>
		/// Creates a new vertex buffer from a span of strongly-typed vertices.
		/// </summary>
		/// <typeparam name="V">Vertex declaration type</typeparam>
		/// <param name="vertices">Span of vertices used to initialize the buffer</param>
		/// <param name="usage">Buffer usage of the vertex buffer</param>
		/// <returns>Unique pointer to the created vertex buffer</returns>
		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(std::span<V> vertices, BufferUsage usage)
		{
			return CreateVertexBuffer(const_cast<const V*>(&vertices[0]), sizeof(V), vertices.size(), usage);
		}

		/// <summary>
		/// Creates a new, uninitialized vertex buffer sized for the specified strongly-typed vertex count.
		/// </summary>
		/// <typeparam name="V">Vertex declaration type</typeparam>
		/// <param name="numVertices">Number of vertices the buffer should hold</param>
		/// <param name="usage">Buffer usage of the vertex buffer</param>
		/// <returns>Unique pointer to the created vertex buffer</returns>
		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(size_t numVertices, BufferUsage usage)
		{
			return CreateVertexBuffer(nullptr, sizeof(V), numVertices, usage);
		}

		/// <summary>
		/// Creates a new deferred graphics command list for recording rendering commands.
		/// </summary>
		/// <returns>Unique pointer to the created graphics command list</returns>
		virtual std::unique_ptr<IGraphicsCommandList> CreateCommandList() = 0;
		/// <summary>
		/// Gets the immediate graphics command list associated with this device.
		/// </summary>
		/// <returns>Pointer to the immediate graphics command list</returns>
		virtual IGraphicsCommandList* ImmediateContext() = 0;

		/// <summary>
		/// Gets the underlying native handle of this graphics device (e.g. an ID3D11Device pointer).
		/// </summary>
		/// <returns>Pointer to the native device handle</returns>
		virtual void* NativeHandle() const noexcept = 0;

		virtual ~IGraphicsDevice() override = default;
	};
}