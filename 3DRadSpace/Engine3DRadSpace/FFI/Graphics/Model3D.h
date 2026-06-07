#pragma once
#include "ModelMesh.h"
#include "../Math/BoundingSphere.h"
#include "../Math/BoundingBox.h"

typedef void* E3DRSP_IGraphicsDevice;
struct E3DRSP_Matrix4x4;

typedef void* E3DRSP_Model3D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_Model3D EDRSP_Model3D_Create(E3DRSP_IGraphicsDevice device, const char* path);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_Draw(E3DRSP_Model3D model);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_Draw2(E3DRSP_Model3D model, const E3DRSP_Matrix4x4* transform);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_DrawEffect(E3DRSP_Model3D model, E3DRSP_Effect effect);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_DrawEffect2(E3DRSP_Model3D model, E3DRSP_Effect effect, const E3DRSP_Matrix4x4* transform);
	E3DRSP_FFI_EXPORT size_t EDRSP_Model3D_NumMeshes(E3DRSP_Model3D model);
	E3DRSP_FFI_EXPORT E3DRSP_ModelMesh EDRSP_Model3D_GetMesh(E3DRSP_Model3D model, size_t index);
	E3DRSP_FFI_EXPORT E3DRSP_BoundingBox EDRSP_Model3D_GetBoundingBox(E3DRSP_Model3D model);
	E3DRSP_FFI_EXPORT E3DRSP_BoundingSphere EDRSP_Model3D_GetBoundingSphere(E3DRSP_Model3D model);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_SetShader(E3DRSP_Model3D model, E3DRSP_Effect effect);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_SetShaders(E3DRSP_Model3D model, E3DRSP_Effect* effects, size_t numEffects);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_SetTransform(E3DRSP_Model3D model, const E3DRSP_Matrix4x4* matrix4x4);
	E3DRSP_FFI_EXPORT void EDRSP_Model3D_Destroy(E3DRSP_Model3D model);
#ifdef __cplusplus
}
#endif