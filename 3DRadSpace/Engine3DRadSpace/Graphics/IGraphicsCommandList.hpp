#pragma once
#include "IGPUResource.hpp"
#include "../Math/Color.hpp"
#include "Viewport.hpp"
#include "VertexTopology.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IRenderTarget;
	class IDepthStencilBuffer;
	class IDepthStencilState;
	class IVertexBuffer;
	class IIndexBuffer;
	class IShader;
	class IRasterizerState;
	class IBlendState;
	class IGPUBuffer;
	class IGPUMultiBuffer;

	/// <summary>
	/// Represents a graphics command list interface for issuing rendering commands to the GPU.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IGraphicsCommandList : public IGPUResource
	{
	protected:
		IGraphicsCommandList() = default;

		IGraphicsCommandList(const IGraphicsCommandList&) = delete;
		IGraphicsCommandList& operator=(const IGraphicsCommandList&) = delete;

		IGraphicsCommandList(IGraphicsCommandList&&) noexcept = default;
		IGraphicsCommandList& operator=(IGraphicsCommandList&&) noexcept = default;
	public:
		/// <summary>
		///	Clears the backbuffer with the specified color and clears the depth buffer.
		/// </summary>
		/// <param name="clearColor">Color to set the backbuffer to</param>
		virtual void Clear(const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) = 0;
		/// <summary>
		/// Clears the specified render target with the given color.
		/// </summary>
		/// <param name="rt">Render target to clear</param>
		/// <param name="clearColor">Color to set the render target to</param>
		virtual void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) = 0;
		/// <summary>
		/// Clears the specified depth buffer.
		/// </summary>
		/// <param name="depth">Depth buffer</param>
		virtual void ClearDepthBuffer(IDepthStencilBuffer* depth) = 0;

		/// <summary>
		/// Sets the default viewport for rendering.
		/// </summary>
		/// <remarks>
		/// The default viewport is speficied as (X: 0, Y: 0, Width: BackBufferWidth, Height: BackBufferHeight, MinDepth: 0.0f, MaxDepth: 1.0f).
		/// </remarks>
		virtual void SetViewport() = 0;
		/// <summary>
		/// Sets an explicit viewport for rendering for the first render target.
		/// </summary>
		/// <param name="viewport">Given viewport</param>
		virtual void SetViewport(const Viewport& viewport) = 0;

		/// <summary>
		/// Sets explicit viewports for rendering all supported (8) render targets.
		/// </summary>
		/// <param name="viewports">Array of viewports to set</param>
		virtual void SetViewports(std::span<Viewport> viewports) = 0;
		/// <summary>
		/// Gets the viewport used for the first render target.
		/// </summary>
		/// <returns>Viewport used for the first render target</returns>
		virtual Viewport GetViewport() = 0;

		/// <summary>
		/// Sets the first render target.
		/// </summary>
		/// <param name="renderTarget">Render target to set. If null, the backbuffer will be used.</param>
		virtual void SetRenderTarget(IRenderTarget* renderTarget) = 0;
		/// <summary>
		/// Sets multiple render target views.
		/// </summary>
		/// <param name="rtvs">Render target views.</param>
		virtual void SetRenderTargets(const std::array<IRenderTarget*, 8>& rtvs) = 0;

		/// <summary>
		///	Unbinds all render target views and depth stencil view from the output merger stage.
		/// </summary>
		virtual void UnbindRenderTargetAndDepth() = 0;

		/// <summary>
		/// Unbinds only the depth buffer from the output merger stage.
		/// </summary>
		virtual void UnbindDepthBuffer() = 0;

		/// <summary>
		/// Sets the render target and depth buffer.
		/// </summary>
		/// <param name="renderTarget">Render target to set. If null, the backbuffer will be used.</param>
		/// <param name="depthBuffer">Depth buffer to set. If null, the default depth stencil buffer will be used.</param>
		virtual void SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) = 0;
		
		/// <summary>
		/// Sets the render target and disables the depth buffer.
		/// </summary>
		/// <param name="renderTarget">Render target to set. If null, the backbuffer will be used.</param>
		virtual void SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) = 0;

		/// <summary>
		/// Gets the currently set render targets.
		/// </summary>
		/// <returns>Array of currently set render targets</returns>
		virtual std::array<IRenderTarget*, 8> GetRenderTargets() = 0;
		/// <summary>
		/// Gets the currently set depth stencil buffer.
		/// </summary>
		/// <returns>Currently set depth stencil buffer</returns>
		virtual IDepthStencilBuffer* GetDepthStencilBuffer() = 0;

		/// <summary>
		/// Draws the specified vertex buffer starting from the given slot.
		/// </summary>
		/// <param name="vertexBuffer">Vertex buffer to draw</param>
		/// <param name="startSlot">Starting slot for drawing</param>
		virtual void DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot = 0) = 0;
		/// <summary>
		/// Draws the specified vertex buffer with indices from the given index buffer.
		/// </summary>
		/// <param name="vertexBuffer">Vertices to be drawn</param>
		/// <param name="indexBuffer">Index buffer containing indices</param>
		virtual void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer) = 0;
		/// <summary>
		/// Draws the specified vertex buffer with indices from the given index buffer, using the specified number of indices.
		/// </summary>
		/// <param name="vertexBuffer">Vertices to be drawn</param>
		/// <param name="indexBuffer">Index buffer containing indices</param>
		/// <param name="numIndices">Number of indices to draw</param>
		virtual void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) = 0;

		/// <summary>
		///	Sets the specified shader to the rendering pipeline.
		/// </summary>
		/// <param name="shader">Shader to set</param>
		virtual void SetShader(IShader* shader) = 0;

		/// <summary>
		///	Sets the rasterizer state.
		/// </summary>
		/// <param name="state">Rasterizer state</param>
		virtual void SetRasterizerState(const IRasterizerState* state) = 0;

		/// <summary>
		/// Sets the depth/stencil buffer for the output merger stage.
		/// </summary>
		/// <param name="depthBuffer">Depth/stencil buffer. If null, the default depth stencil state will be used.</param>
		virtual void SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) = 0;
		/// <summary>
		/// Sets the depth/stencil state for the output merger stage.
		/// </summary>
		/// <param name="depthState">Depth/stencil state</param>
		/// <param name="ref">Reference value for the depth/stencil state</param>
		virtual void SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) = 0;

		/// <summary>
		///	Sets the blend state for the output merger stage.
		/// </summary>
		/// <param name="blendState">Blend state</param>
		/// <param name="blendFactor">Blend factor</param>
		/// <param name="sampleMask">Sample mask</param>
		virtual void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) = 0;

		/// <summary>
		/// Sets the vertex topology for rendering.
		/// </summary>
		virtual void SetTopology(VertexTopology topology) = 0;
		/// <summary>
		/// Draws vertices and index buffer of unknown data size.
		/// </summary>
		virtual void DrawAuto() = 0;
		/// <summary>
		///	Present the backbuffer to the screen.
		/// </summary>
		virtual void Present() = 0;
		
		/// <summary>
		/// Saves the backbuffer to a file.
		/// </summary>
		/// <param name="path">File path to save the backbuffer</param>
		virtual void SaveBackBufferToFile(const std::filesystem::path& path) = 0;

		/// <summary>
		/// Resizes the backbuffer to the specified new resolution.
		/// </summary>
		/// <param name="newResolution">New resolution in pixels for the backbuffer.</param>
		virtual void ResizeBackBuffer(const Math::Point& newResolution) = 0;
		/// <summary>
		/// Sets the fullscreen mode.
		/// </summary>
		/// <param name="fullscreen">True to set fullscreen mode, false for windowed mode.</param>	
		virtual void SetFullScreen(bool fullscreen) = 0;
		///<summary>
		/// Checks if the associated device is in fullscreen mode.
		/// </summary>
		virtual bool IsFullScreen() const = 0;

		/// <summary>
		///	Copies data from the source GPU buffer to the destination GPU buffer.
		/// </summary>
		/// <param name="dest">Destination GPU buffer</param>
		/// <param name="src">Source GPU buffer</param>
		virtual void Copy(IGPUBuffer* dest, IGPUBuffer* src) = 0;
		/// <summary>
		/// Copies data from the source GPU multi-buffer to the destination GPU multi-buffer.
		/// </summary>
		/// <param name="dest">Destination GPU multi-buffer</param>
		/// <param name="src">Source GPU multi-buffer</param>
		virtual void Copy(IGPUMultiBuffer* dest, IGPUMultiBuffer* src) = 0;

		virtual ~IGraphicsCommandList() = default;
	};
}