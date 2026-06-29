#pragma once
#include "IGraphicsDevice.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "ISamplerState.h"
#include "ITexture2D.h"
#include "VertexDeclarations.h"
#include "../Math/BoundingSphere.h"
#include "../Math/BoundingBox.h"
#include "IGraphicsCommandList.h"
#include "../Math/Matrix4x4.h"

typedef void* E3DRSP_Effect;

typedef void* E3DRSP_ModelMeshPart;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_ModelMeshPart E3DRSP_ModelMeshPart_Create(
		E3DRSP_IGraphicsDevice device,
		void* vertices,
		size_t numVerts,
		size_t structSize,
		unsigned* indices,
		size_t numIndices,
		E3DRSP_Effect shaders
	);

	E3DRSP_FFI_EXPORT E3DRSP_ModelMeshPart E3DRSP_ModelMeshPart_Create2(
		E3DRSP_IVertexBuffer vertexBuffer,
		E3DRSP_IIndexBuffer indexBuffer,
		E3DRSP_Effect shaders
	);

	E3DRSP_FFI_EXPORT void E3DRSP_ModelMeshPart_Draw(E3DRSP_ModelMeshPart meshPart);
	E3DRSP_FFI_EXPORT void E3DRSP_ModelMeshPart_DrawEffect(E3DRSP_ModelMeshPart meshPart, E3DRSP_Effect effect);
	E3DRSP_FFI_EXPORT E3DRSP_BoundingBox E3DRSP_ModelMeshPart_GetBoundingBox(E3DRSP_ModelMeshPart meshPart);
	E3DRSP_FFI_EXPORT E3DRSP_BoundingSphere E3DRSP_ModelMeshPart_GetBoundingSphere(E3DRSP_ModelMeshPart meshPart);

	E3DRSP_FFI_EXPORT E3DRSP_IVertexBuffer E3DRSP_ModelMeshPart_GetVertexBuffer(E3DRSP_ModelMeshPart meshPart);
	E3DRSP_FFI_EXPORT E3DRSP_IIndexBuffer E3DRSP_ModelMeshPart_GetIndexBuffer(E3DRSP_ModelMeshPart meshPart);

	E3DRSP_FFI_EXPORT E3DRSP_Effect E3DRSP_ModelMeshPart_GetShaders(E3DRSP_ModelMeshPart meshPart);
	E3DRSP_FFI_EXPORT void E3DRSP_ModelMeshPart_SetShaders(E3DRSP_ModelMeshPart meshPart, E3DRSP_Effect shaders);

	E3DRSP_FFI_EXPORT E3DRSP_Matrix4x4 E3DRSP_ModelMeshPart_GetTransform(E3DRSP_ModelMeshPart meshPart);
	E3DRSP_FFI_EXPORT void E3DRSP_ModelMeshPart_SetTransform(E3DRSP_ModelMeshPart meshPart, const E3DRSP_Matrix4x4* transform);

	E3DRSP_FFI_EXPORT void E3DRSP_ModelMeshPart_Destroy(E3DRSP_ModelMeshPart meshPart);
#ifdef __cplusplus
}
#endif