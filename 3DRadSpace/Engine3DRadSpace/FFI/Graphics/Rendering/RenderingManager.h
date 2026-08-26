#pragma once
#include "../../Core/IService.h"
#include "../IGraphicsDevice.h"
#include "../ModelMeshPart.h"
#include "../Model3D.h"
#include "RenderPassType.h"
#include "DirectionalLight.h"

typedef void* E3DRSP_RenderingManager;
typedef void* E3DRSP_IRenderer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_RenderingManager E3DRSP_RenderingManager_Create(E3DRSP_IGraphicsDevice device);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_Add(E3DRSP_RenderingManager manager, E3DRSP_IRenderer renderer);
	E3DRSP_FFI_EXPORT E3DRSP_IRenderer E3DRSP_RenderingManager_At(E3DRSP_RenderingManager manager, size_t index);
	E3DRSP_FFI_EXPORT size_t E3DRSP_RenderingManager_NumPasses(E3DRSP_RenderingManager manager);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_Remove(E3DRSP_RenderingManager manager, size_t index);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_Clear(E3DRSP_RenderingManager manager);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_Draw(E3DRSP_RenderingManager manager, E3DRSP_Model3D model, E3DRSP_RenderPassType passType);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_Draw2(E3DRSP_RenderingManager manager, E3DRSP_ModelMeshPart model, E3DRSP_RenderPassType passType);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_Execute(E3DRSP_RenderingManager manager);

	E3DRSP_FFI_EXPORT E3DRSP_RenderingManager E3DRSP_RenderingManager_CreateForward(E3DRSP_IGraphicsDevice device);
	E3DRSP_FFI_EXPORT E3DRSP_RenderingManager E3DRSP_RenderingManager_CreateTrivial(E3DRSP_IGraphicsDevice device);
	E3DRSP_FFI_EXPORT E3DRSP_RenderingManager E3DRSP_RenderingManager_CreateNull(E3DRSP_IGraphicsDevice device);

	E3DRSP_FFI_EXPORT E3DRSP_DirectionalLight E3DRSP_RenderingManager_GetDirectionalLight(E3DRSP_RenderingManager manager);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_SetDirectionalLight(E3DRSP_RenderingManager manager, const E3DRSP_DirectionalLight *light);
	
	E3DRSP_FFI_EXPORT E3DRSP_IGraphicsDevice E3DRSP_RenderingManager_GetGraphicsDevice(E3DRSP_RenderingManager manager);
	E3DRSP_FFI_EXPORT void E3DRSP_RenderingManager_Destroy(E3DRSP_RenderingManager manager);
#ifdef __cplusplus
}
#endif