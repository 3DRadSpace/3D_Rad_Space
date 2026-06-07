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

	class E3DRSP_GRAPHICS_EXPORT IGraphicsCommandList : public IGPUResource
	{
	protected:
		IGraphicsCommandList() = default;

		IGraphicsCommandList(const IGraphicsCommandList&) = delete;
		IGraphicsCommandList& operator=(const IGraphicsCommandList&) = delete;

		IGraphicsCommandList(IGraphicsCommandList&&) noexcept = default;
		IGraphicsCommandList& operator=(IGraphicsCommandList&&) noexcept = default;
	public:
		virtual void Clear(const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) = 0;
		virtual void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) = 0;
		virtual void ClearDepthBuffer(IDepthStencilBuffer* depth) = 0;

		virtual void SetViewport() = 0;
		virtual void SetViewport(const Viewport& viewport) = 0;

		virtual void SetViewports(std::span<Viewport> viewports) = 0;
		virtual Viewport GetViewport() = 0;

		virtual void SetRenderTarget(IRenderTarget* renderTarget) = 0;

		virtual void UnbindRenderTargetAndDepth() = 0;

		virtual void UnbindDepthBuffer() = 0;

		virtual void SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) = 0;

		virtual void SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) = 0;

		virtual void DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot = 0) = 0;
		virtual void DrawVertexBufferWithIndices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer) = 0;
		virtual void DrawVertexBufferWithIndices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) = 0;

		virtual void SetShader(IShader* shader) = 0;

		virtual void SetRasterizerState(const IRasterizerState* state) = 0;

		virtual void SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) = 0;
		virtual void SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) = 0;

		virtual void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) = 0;

		virtual void SetTopology(VertexTopology topology) = 0;
		virtual void DrawAuto() = 0;
		virtual void Present() = 0;

		virtual void SaveBackBufferToFile(const std::filesystem::path& path) = 0;

		virtual void ResizeBackBuffer(const Math::Point& newResolution) = 0;
		virtual void SetFullScreen(bool fullscreen) = 0;
		virtual bool IsFullScreen() const = 0;

		virtual void Copy(IGPUBuffer* dest, IGPUBuffer* src) = 0;
		virtual void Copy(IGPUMultiBuffer* dest, IGPUMultiBuffer* src) = 0;

		virtual ~IGraphicsCommandList() = default;
	};
}