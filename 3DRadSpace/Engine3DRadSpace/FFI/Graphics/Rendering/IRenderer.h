#pragma once
#include "../ModelMeshPart.h"
#include "RenderPassType.h"
#include "MaterialDescriptor.h"
#include "RenderingManager.h"

typedef void* E3DRSP_IRenderer;

typedef struct E3DRSP_MeshPartDrawInfo
{
	E3DRSP_ModelMeshPart* Part;
	E3DRSP_RenderPassType PassType;
	E3DRSP_Matrix4x4 World;
	E3DRSP_Matrix4x4 View;
	E3DRSP_Matrix4x4 Projection;
};

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_IRenderer_Begin(E3DRSP_IRenderer renderer);
	E3DRSP_FFI_EXPORT void E3DRSP_IRenderer_Draw(E3DRSP_IRenderer renderer, E3DRSP_ModelMeshPart mesh, const E3DRSP_MaterialDescriptor* descriptor);
	E3DRSP_FFI_EXPORT void E3DRSP_IRenderer_End(E3DRSP_IRenderer renderer);
	E3DRSP_FFI_EXPORT bool E3DRSP_IRenderer_IsRenderPassTypeSupported(const E3DRSP_IRenderer renderer, E3DRSP_RenderPassType passType);
	E3DRSP_FFI_EXPORT void E3DRSP_IRenderer_Destroy(E3DRSP_IRenderer renderer);
#ifdef __cplusplus
}
#endif