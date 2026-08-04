#pragma once
#include "IGPUResource.h"
#include "../Math/Color.h"
#include "../Math/Point.h"
#include "Viewport.h"
#include "VertexTopology.h"

typedef void* E3DRSP_IGraphicsCommandList;

typedef void* E3DRSP_IRenderTarget;
typedef void* E3DRSP_IDepthStencilBuffer;
typedef void* E3DRSP_IDepthStencilState;
typedef void* E3DRSP_IVertexBuffer;
typedef void* E3DRSP_IIndexBuffer;
typedef void* E3DRSP_IShader;
typedef void* E3DRSP_IRasterizerState;
typedef void* E3DRSP_IBlendState;
typedef void* E3DRSP_IGPUBuffer;
typedef void* E3DRSP_IGPUMultiBuffer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_Clear(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_Color* clearColor);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_ClearRenderTarget(
		E3DRSP_IGraphicsCommandList cmd,
		E3DRSP_IRenderTarget rt, 
		const E3DRSP_Color* clearColor
	);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_ClearDepthBuffer(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IDepthStencilBuffer depth);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetViewport(E3DRSP_IGraphicsCommandList cmd);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetViewport2(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_Viewport* viewport);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetViewports(E3DRSP_IGraphicsCommandList cmd, E3DRSP_Viewport** viewports, size_t numViewports);
	E3DRSP_FFI_EXPORT E3DRSP_Viewport E3DRSP_IGraphicsCommandList_GetViewport(E3DRSP_IGraphicsCommandList cmd);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetRenderTarget(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IRenderTarget renderTarget);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_UnbindRenderTargetAndDepth(E3DRSP_IGraphicsCommandList cmd);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_UnbindDepthBuffer(E3DRSP_IGraphicsCommandList cmd);

	E3DRSP_FFI_EXPORT void SE3DRSP_IGraphicsCommandList_SetRenderTargetAndDepth(
		E3DRSP_IGraphicsCommandList cmd,
		E3DRSP_IRenderTarget renderTarget,
		E3DRSP_IDepthStencilBuffer depthBuffer
	);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetRenderTargetAndDisableDepth(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IRenderTarget renderTarget);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_DrawVertexBuffer(
		E3DRSP_IGraphicsCommandList cmd,
		E3DRSP_IVertexBuffer vertexBuffer,
		unsigned startSlot
	);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_DrawVertexBufferWithindices(
		E3DRSP_IGraphicsCommandList cmd,
		E3DRSP_IVertexBuffer vertexBuffer,
		E3DRSP_IIndexBuffer indexBuffer
	);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_DrawVertexBufferWithindices2(
		E3DRSP_IGraphicsCommandList cmd,
		E3DRSP_IVertexBuffer vertexBuffer,
		E3DRSP_IIndexBuffer indexBuffer,
		unsigned numIndices
	);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetShader(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IShader shader);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetRasterizerState(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_IRasterizerState state);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetDepthStencilBuffer(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IDepthStencilBuffer depthBuffer);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetDepthStencilState(
		E3DRSP_IGraphicsCommandList cmd,
		E3DRSP_IDepthStencilState depthState,
		unsigned ref
	);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetBlendState(
		E3DRSP_IGraphicsCommandList cmd,
		E3DRSP_IBlendState blendState,
		const E3DRSP_Color* blendFactor,
		unsigned sampleMask
	);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetTopology(E3DRSP_IGraphicsCommandList cmd, E3DRSP_VertexTopology topology);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_DrawAuto(E3DRSP_IGraphicsCommandList cmd);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_Present(E3DRSP_IGraphicsCommandList cmd);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SaveBackBufferToFile(E3DRSP_IGraphicsCommandList cmd, const char* path);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_ResizeBackBuffer(E3DRSP_IGraphicsCommandList cmd, const E3DRSP_Point* newResolution);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_SetFullScreen(E3DRSP_IGraphicsCommandList cmd, bool fullscreen);
	E3DRSP_FFI_EXPORT bool E3DRSP_IGraphicsCommandList_IsFullScreen(E3DRSP_IGraphicsCommandList cmd);

	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_Copy(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IGPUBuffer* dest, E3DRSP_IGPUBuffer* src);
	E3DRSP_FFI_EXPORT void E3DRSP_IGraphicsCommandList_CopyMulti(E3DRSP_IGraphicsCommandList cmd, E3DRSP_IGPUMultiBuffer* dest, E3DRSP_IGPUMultiBuffer* src);
#ifdef __cplusplus
}
#endif