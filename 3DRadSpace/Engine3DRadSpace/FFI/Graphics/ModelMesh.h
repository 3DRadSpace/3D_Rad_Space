#pragma once
#include "ModelMeshPart.h"

struct E3DRSP_BoundingBox;
struct E3DRSP_BoundingSphere;

typedef void* E3DRSP_ModelMesh;

#ifdef __cplusplus
extern "C"
{
#endif 
	E3DRSP_FFI_EXPORT E3DRSP_ModelMesh E3DRSP_ModelMesh_Create(E3DRSP_ModelMeshPart* parts, size_t numParts);
	E3DRSP_FFI_EXPORT void E3DRSP_ModelMesh_AddMeshPart(E3DRSP_ModelMesh mesh, E3DRSP_ModelMeshPart part);
	E3DRSP_FFI_EXPORT E3DRSP_ModelMeshPart E3DRSP_ModelMesh_GetMeshPart(E3DRSP_ModelMesh mesh, unsigned index);
	E3DRSP_FFI_EXPORT size_t E3DRSP_ModelMesh_NumMeshParts(E3DRSP_ModelMesh mesh);
	E3DRSP_FFI_EXPORT void E3DRSP_ModelMesh_Draw(E3DRSP_ModelMesh mesh);

	E3DRSP_FFI_EXPORT E3DRSP_BoundingBox E3DRSP_ModelMesh_GetBoundingBox(E3DRSP_ModelMesh mesh);
	E3DRSP_FFI_EXPORT E3DRSP_BoundingSphere E3DRSP_ModelMesh_GetBoundingSphere(E3DRSP_ModelMesh mesh);

	E3DRSP_FFI_EXPORT void E3DRSP_ModelMesh_Destroy(E3DRSP_ModelMesh mesh);
#ifdef __cplusplus
}
#endif