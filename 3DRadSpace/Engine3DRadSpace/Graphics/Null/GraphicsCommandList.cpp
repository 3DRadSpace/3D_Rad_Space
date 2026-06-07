#include "GraphicsCommandList.hpp"
#include "RasterizerState.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;
using namespace Engine3DRadSpace::Math;

GraphicsCommandList::GraphicsCommandList(GraphicsDevice* device)
{
	(void)device;
}

void GraphicsCommandList::Clear(const Math::Color& clearColor)
{
	(void)clearColor;
}

void GraphicsCommandList::ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor)
{
	(void)rt;
	(void)clearColor;
}

void GraphicsCommandList::ClearDepthBuffer(IDepthStencilBuffer* depth)
{
	(void)depth;
}

void GraphicsCommandList::SetViewport()
{
}

void GraphicsCommandList::SetViewport(const Viewport& viewport)
{
	(void)viewport;
}

void GraphicsCommandList::SetViewports(std::span<Viewport> viewports)
{
	(void)viewports;
}

Viewport GraphicsCommandList::GetViewport()
{
	return Viewport(RectangleF(), 0, 0);
}

void GraphicsCommandList::SetRenderTarget(IRenderTarget* renderTarget)
{
	(void)renderTarget;
}

void GraphicsCommandList::UnbindRenderTargetAndDepth()
{
}

void GraphicsCommandList::UnbindDepthBuffer()
{
}

void GraphicsCommandList::SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer)
{
	(void)renderTarget;
	(void)depthBuffer;
}

void GraphicsCommandList::SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget)
{
	(void)renderTarget;
}

void GraphicsCommandList::DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot)
{
	(void)vertexBuffer;
	(void)startSlot;
}

void GraphicsCommandList::DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer)
{
	(void)vertexBuffer;
	(void)indexBuffer;
}
void GraphicsCommandList::DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices)
{
	(void)vertexBuffer;
	(void)indexBuffer;
	(void)numIndices;
}

void GraphicsCommandList::SetShader(IShader* shader)
{
	(void)shader;
}

void GraphicsCommandList::SetRasterizerState(const IRasterizerState* state)
{
	(void)state;
}

//std::unique_ptr<IRasterizerState> GraphicsCommandList::GetRasterizerState()
//{
//	return std::make_unique<RasterizerState>(_device);
//}

void GraphicsCommandList::SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer)
{
	(void)depthBuffer;
}

void GraphicsCommandList::SetDepthStencilState(IDepthStencilState* depthState, unsigned ref)
{
	(void)depthState;
	(void)ref;
}

void GraphicsCommandList::SetBlendState(IBlendState* blendState, const Math::Color& blendFactor, unsigned sampleMask)
{
	(void)blendState;
	(void)blendFactor;
	(void)sampleMask;
}

void GraphicsCommandList::SetTopology(VertexTopology topology)
{
	(void)topology;
}

void GraphicsCommandList::DrawAuto()
{
}

void GraphicsCommandList::Present()
{
}

void GraphicsCommandList::SaveBackBufferToFile(const std::filesystem::path& path)
{
	(void)path;
}

void GraphicsCommandList::ResizeBackBuffer(const Math::Point& newResolution)
{
	(void)newResolution;
}

void GraphicsCommandList::SetFullScreen(bool fullscreen)
{
	(void)fullscreen;
}

bool GraphicsCommandList::IsFullScreen() const
{
	return false;
}

void GraphicsCommandList::Copy(IGPUBuffer* dest, IGPUBuffer* src)
{
	(void)dest;
	(void)src;
}

void GraphicsCommandList::Copy(IGPUMultiBuffer* dest, IGPUMultiBuffer* src)
{
	(void)dest;
	(void)src;
}

void* GraphicsCommandList::GetHandle() const noexcept
{
	return nullptr;
}

IGraphicsDevice* GraphicsCommandList::GetGraphicsDevice() const noexcept
{
	return nullptr;
}