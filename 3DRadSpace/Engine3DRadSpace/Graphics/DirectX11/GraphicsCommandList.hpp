#pragma once
#include "../IGraphicsCommandList.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class VertexBuffer;
	class IndexBuffer;

	class Texture2D;
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
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_DX11_EXPORT GraphicsCommandList : public IGraphicsCommandList
	{
	protected:
		GraphicsDevice* _device;
		ID3D11DeviceContext* _context;
	public:
		GraphicsCommandList(GraphicsDevice* device);

		void Clear(const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) override;
		void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) override;
		void ClearDepthBuffer(IDepthStencilBuffer* depth) override;

		void SetViewport() override;
		void SetViewport(const Viewport& viewport) override;

		void SetViewports(std::span<Viewport> viewports) override;
		Viewport GetViewport() override;

		/// <summary>
		/// Sets the current render target. Depth buffer is set to the default depth buffer.
		/// </summary>
		/// <param name="remderTarget">Render target pointer reference. Using null will use the backbuffer.</param>
		void SetRenderTarget(IRenderTarget* renderTarget) override;
		/// <summary>
		/// Unbinds the current render target and depth buffer. 
		/// </summary>
		/// <remarks>
		/// When called, there's no valid render surface that's assigned to the GPU. 
		/// </remarks>
		void UnbindRenderTargetAndDepth() override;
		/// <summary>
		/// Unbinds the current depth buffer.
		/// </summary>
		void UnbindDepthBuffer() override;
		/// <summary>
		/// Sets both render target and depth stencil buffer.
		/// </summary>
		/// <param name="renderTarget">Render surface to be drawn into. If null, it is set to the backbuffer.</param>
		/// <param name="depthBuffer">Depth stencil buffer. If null, will be set to the default non-null buffer.</param>
		void SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) override;
		/// <summary>
		/// Sets the render target, but unbinds the depth buffer.
		/// </summary>
		/// <param name="renderTarget">Render surface to be drawn into. If null, it is set to the backbuffer.</param>
		void SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) override;

		/// <summary>
		/// Draws a vertex buffer into the selected render target.
		/// </summary>
		/// <param name="vertexBuffer">Vertex buffer.</param>
		/// <param name="startSlot">Index of the first buffer.</param>
		void DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot = 0) override;
		/// <summary>
		/// Draws a vertex buffer ordered by a index buffer into the selected render target.
		/// </summary>
		/// <param name="vertexBuffer">Vertex buffer.</param>
		/// <param name="indexBuffer">Index buffer.</param>
		void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer) override;
		void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) override;

		/// <summary>
		/// Sets a shader for the graphics pipeline.
		/// </summary>
		/// <param name="shader">Either a vertex shader, fragment shader, geometry shader, etc...</param>
		void SetShader(IShader* shader) override;

		void SetRasterizerState(const IRasterizerState* state) override;
		//std::unique_ptr<IRasterizerState> GetRasterizerState() override;

		void SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) override;
		void SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) override;

		void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) override;

		/// <summary>
		/// Sets the topology used by the vertex buffer.
		/// </summary>
		/// <param name="topology"></param>
		void SetTopology(VertexTopology topology) override;
		void DrawAuto() override;
		/// <summary>
		/// Swaps the front and backbuffer, thus outputting the backbuffer to the screen.
		/// </summary>
		void Present() override;

		/// <summary>
		/// Writes the backbuffer to a file. 
		/// </summary>
		/// <param name="path">PNG format image path.</param>
		void SaveBackBufferToFile(const std::filesystem::path& path) override;

		/// <summary>
		/// Resizes the back buffer, stencil buffer.
		/// </summary>
		/// <param name="newResolution">New resolution. Use 0,0 to match window size.</param>
		/// <remarks>
		/// Number of swap chain textures is preserved.
		/// Texture format will be same as the previous pixel format.
		/// </remarks>
		void ResizeBackBuffer(const Math::Point& newResolution) override;
		/// <summary>
		/// Switches the fullscreen state.
		/// </summary>
		/// <param name="fullscreen">True to set fullscreen, false to set windowed mode.</param>
		void SetFullScreen(bool fullscreen) override;

		bool IsFullScreen() const override;

		void Copy(IGPUBuffer* dest, IGPUBuffer* src) override;
		void Copy(IGPUMultiBuffer* dest, IGPUMultiBuffer* src) override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~GraphicsCommandList() override = default;
	
		friend class VertexBuffer;
		friend class IndexBuffer;
		friend class Texture2D;
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
	};
}