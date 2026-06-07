#include "../../Graphics/IGraphicsCommandList.hpp"
#include "IGraphicsCommandList.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void E3DRSP_IGraphicsCommandList_Clear(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_Color* clearColor)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->Clear(*std::bit_cast<const Math::Color*>(clearColor));
}

void E3DRSP_IGraphicsCommandList_ClearRenderTarget(
	E3DRSP_IGraphicsCommandList cmd,
	E3DRSP_IRenderTarget rt,
	const E3DRSP_Color* clearColor
)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->ClearRenderTarget(
		reinterpret_cast<IRenderTarget*>(rt),
		std::bit_cast<const Math::Color>(*clearColor)
	);
}

void E3DRSP_IGraphicsCommandList_ClearDepthBuffer(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IDepthStencilBuffer depth)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->ClearDepthBuffer(reinterpret_cast<IDepthStencilBuffer*>(depth));
}

void E3DRSP_IGraphicsCommandList_SetViewport(E3DRSP_IGraphicsCommandList cmd)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetViewport();
}

void E3DRSP_IGraphicsCommandList_SetViewport2(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_Viewport* viewport)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetViewport(std::bit_cast<const Viewport>(*viewport));
}

void E3DRSP_IGraphicsCommandList_SetViewports(E3DRSP_IGraphicsCommandList cmd, E3DRSP_Viewport** viewports, size_t numViewports)
{
	std::vector<Viewport> natViewports;
	natViewports.reserve(numViewports);
	for (size_t i = 0; i < numViewports; i++)
	{
		natViewports.push_back(std::bit_cast<Viewport>(*viewports[i]));
	}

	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetViewports(natViewports);
}

E3DRSP_Viewport E3DRSP_IGraphicsCommandList_GetViewport(E3DRSP_IGraphicsCommandList cmd)
{
	auto vp = reinterpret_cast<IGraphicsCommandList*>(cmd)->GetViewport();
	return std::bit_cast<E3DRSP_Viewport>(vp);
}

void E3DRSP_IGraphicsCommandList_SetRenderTarget(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IRenderTarget renderTarget)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetRenderTarget(reinterpret_cast<IRenderTarget*>(renderTarget));
}

void E3DRSP_IGraphicsCommandList_UnbindRenderTargetAndDepth(E3DRSP_IGraphicsCommandList cmd)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->UnbindRenderTargetAndDepth();
}

void E3DRSP_IGraphicsCommandList_UnbindDepthBuffer(E3DRSP_IGraphicsCommandList cmd)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->UnbindDepthBuffer();
}

void SE3DRSP_IGraphicsCommandList_SetRenderTargetAndDepth(
	E3DRSP_IGraphicsCommandList cmd,
	E3DRSP_IRenderTarget renderTarget,
	E3DRSP_IDepthStencilBuffer depthBuffer
)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetRenderTargetAndDepth(
		reinterpret_cast<IRenderTarget*>(renderTarget),
		reinterpret_cast<IDepthStencilBuffer*>(depthBuffer)
	);
}

void E3DRSP_IGraphicsCommandList_SetRenderTargetAndDisableDepth(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IRenderTarget renderTarget)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetRenderTargetAndDisableDepth(reinterpret_cast<IRenderTarget*>(renderTarget));
}

void E3DRSP_IGraphicsCommandList_DrawVertexBuffer(
	E3DRSP_IGraphicsCommandList cmd,
	E3DRSP_IVertexBuffer vertexBuffer,
	unsigned startSlot
)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->DrawVertexBuffer(
		reinterpret_cast<IVertexBuffer*>(vertexBuffer),
		startSlot
	);
}
void E3DRSP_IGraphicsCommandList_DrawVertexBufferWithindices(
	E3DRSP_IGraphicsCommandList cmd,
	E3DRSP_IVertexBuffer vertexBuffer,
	E3DRSP_IIndexBuffer indexBuffer
)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->DrawVertexBufferWithindices(
		reinterpret_cast<IVertexBuffer*>(vertexBuffer),
		reinterpret_cast<IIndexBuffer*>(indexBuffer)
	);
}
void E3DRSP_IGraphicsCommandList_DrawVertexBufferWithindices2(
	E3DRSP_IGraphicsCommandList cmd,
	E3DRSP_IVertexBuffer vertexBuffer,
	E3DRSP_IIndexBuffer indexBuffer,
	unsigned numIndices
)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->DrawVertexBufferWithindices(
		reinterpret_cast<IVertexBuffer*>(vertexBuffer),
		reinterpret_cast<IIndexBuffer*>(indexBuffer),
		numIndices
	);
}

void E3DRSP_IGraphicsCommandList_SetShader(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IShader shader)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetShader(reinterpret_cast<IShader*>(shader));
}

void E3DRSP_IGraphicsCommandList_SetRasterizerState(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_IRasterizerState state)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetRasterizerState(reinterpret_cast<IRasterizerState*>(state));
}

void E3DRSP_IGraphicsCommandList_SetDepthStencilBuffer(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IDepthStencilBuffer depthBuffer)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetDepthStencilBuffer(reinterpret_cast<IDepthStencilBuffer*>(depthBuffer));
}
void E3DRSP_IGraphicsCommandList_SetDepthStencilState(
	E3DRSP_IGraphicsCommandList cmd,
	E3DRSP_IDepthStencilState depthState,
	unsigned ref
)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetDepthStencilState(
		reinterpret_cast<IDepthStencilState*>(depthState),
		ref
	);
}

void E3DRSP_IGraphicsCommandList_SetBlendState(
	E3DRSP_IGraphicsCommandList cmd,
	E3DRSP_IBlendState blendState,
	const E3DRSP_Color* blendFactor,
	unsigned sampleMask
)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetBlendState(
		reinterpret_cast<IBlendState*>(blendState),
		std::bit_cast<const Math::Color>(*blendFactor),
		sampleMask
	);
}

void E3DRSP_IGraphicsCommandList_SetTopology(E3DRSP_IGraphicsCommandList cmd, E3DRSP_VertexTopology topology)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetTopology(static_cast<VertexTopology>(topology));
}

void E3DRSP_IGraphicsCommandList_DrawAuto(E3DRSP_IGraphicsCommandList cmd)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->DrawAuto();
}
void E3DRSP_IGraphicsCommandList_Present(E3DRSP_IGraphicsCommandList cmd)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->Present();
}

void E3DRSP_IGraphicsCommandList_SaveBackBufferToFile(E3DRSP_IGraphicsCommandList cmd, const char* path)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SaveBackBufferToFile(std::filesystem::path(path));
}

void E3DRSP_IGraphicsCommandList_ResizeBackBuffer(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_Point* newResolution)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->ResizeBackBuffer(std::bit_cast<const Math::Point>(*newResolution));
}
void E3DRSP_IGraphicsCommandList_SetFullScreen(E3DRSP_IGraphicsCommandList cmd, bool fullscreen)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->SetFullScreen(fullscreen);
}

void E3DRSP_IGraphicsCommandList_Copy(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IGPUBuffer* dest, E3DRSP_IGPUBuffer* src)
{
	reinterpret_cast<IGraphicsCommandList*>(cmd)->Copy(
		reinterpret_cast<IGPUBuffer*>(dest),
		reinterpret_cast<IGPUBuffer*>(src)
	);
}