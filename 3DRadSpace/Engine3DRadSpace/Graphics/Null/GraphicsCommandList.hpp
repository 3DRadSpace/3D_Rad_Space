#pragma once
#include "../IGraphicsCommandList.hpp"
#include "GraphicsDevice.hpp"
#include "../../Math/Color.hpp"
#include "../Viewport.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	/// <summary>
	/// Null GraphicsCommandList implementation that doesn't make any GAPI calls.
	/// </summary>
	class E3DRSP_GRAPHICS_NULL_EXPORT GraphicsCommandList final : public IGraphicsCommandList
	{
	public:
		GraphicsCommandList(GraphicsDevice* device);

		virtual void Clear(const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) override;
		virtual void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) override;
		virtual void ClearDepthBuffer(IDepthStencilBuffer* depth) override;

		virtual void SetViewport() override;
		virtual void SetViewport(const Viewport& viewport) override;

		virtual void SetViewports(std::span<Viewport> viewports) override;
		virtual Viewport GetViewport() override;

		virtual void SetRenderTarget(IRenderTarget* renderTarget) override;

		virtual void UnbindRenderTargetAndDepth() override;

		virtual void UnbindDepthBuffer() override;

		virtual void SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) override;

		virtual void SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) override;

		virtual void DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot = 0) override;
		virtual void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer) override;
		virtual void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) override;

		virtual void SetShader(IShader* shader) override;

		virtual void SetRasterizerState(const IRasterizerState* state) override;

		virtual void SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) override;
		virtual void SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) override;

		virtual void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) override;

		virtual void SetTopology(VertexTopology topology) override;
		virtual void DrawAuto() override;
		virtual void Present() override;

		virtual void SaveBackBufferToFile(const std::filesystem::path& path) override;

		virtual void ResizeBackBuffer(const Math::Point& newResolution) override;
		virtual void SetFullScreen(bool fullscreen) override;
		virtual bool IsFullScreen() const override;

		virtual void Copy(IGPUBuffer* dest, IGPUBuffer* src) override;
		virtual void Copy(IGPUMultiBuffer* dest, IGPUMultiBuffer* src) override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~GraphicsCommandList() override = default;
	};
}