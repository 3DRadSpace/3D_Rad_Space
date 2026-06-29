#include "ModelMesh.h"
#include "../../Graphics/ModelMeshPart.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_ModelMeshPart E3DRSP_ModelMeshPart_Create(
	E3DRSP_IGraphicsDevice device,
	void* vertices,
	size_t numVerts,
	size_t structSize,
	unsigned* indices,
	size_t numIndices,
	E3DRSP_Effect shaders
)
{
	return new ModelMeshPart(
		reinterpret_cast<IGraphicsDevice*>(device),
		vertices,
		numVerts,
		structSize,
		std::span<unsigned>(indices, numIndices),
		reinterpret_cast<Effect*>(shaders)
	);
}

E3DRSP_ModelMeshPart E3DRSP_ModelMeshPart_Create2(
	E3DRSP_IVertexBuffer vertexBuffer,
	E3DRSP_IIndexBuffer indexBuffer,
	E3DRSP_Effect shaders
)
{
	return new ModelMeshPart(
		reinterpret_cast<IVertexBuffer*>(vertexBuffer),
		reinterpret_cast<IIndexBuffer*>(indexBuffer),
		reinterpret_cast<Effect*>(shaders)
	);
}

void E3DRSP_ModelMeshPart_Draw(E3DRSP_ModelMeshPart meshPart)
{
	static_cast<ModelMeshPart*>(meshPart)->Draw();
}

void E3DRSP_ModelMeshPart_DrawEffect(E3DRSP_ModelMeshPart meshPart, E3DRSP_Effect effect)
{
	static_cast<ModelMeshPart*>(meshPart)->Draw(reinterpret_cast<Effect*>(effect));
}

E3DRSP_BoundingBox E3DRSP_ModelMeshPart_GetBoundingBox(E3DRSP_ModelMeshPart meshPart)
{
	auto boundingBox = static_cast<ModelMeshPart*>(meshPart)->GetBoundingBox();
	return E3DRSP_BoundingBox{
		{ boundingBox.Position.X, boundingBox.Position.Y, boundingBox.Position.Z },
		{ boundingBox.Scale.X, boundingBox.Scale.Y, boundingBox.Scale.Z }
	};
}

E3DRSP_BoundingSphere E3DRSP_ModelMeshPart_GetBoundingSphere(E3DRSP_ModelMeshPart meshPart)
{
	auto boundingSphere = static_cast<ModelMeshPart*>(meshPart)->GetBoundingSphere();
	return E3DRSP_BoundingSphere{
		{ boundingSphere.Center.X, boundingSphere.Center.Y, boundingSphere.Center.Z },
		boundingSphere.Radius
	};
}

E3DRSP_IVertexBuffer E3DRSP_ModelMeshPart_GetVertexBuffer(E3DRSP_ModelMeshPart meshPart)
{
	return reinterpret_cast<ModelMeshPart*>(meshPart)->GetVertexBuffer();
}

E3DRSP_IIndexBuffer E3DRSP_ModelMeshPart_GetIndexBuffer(E3DRSP_ModelMeshPart meshPart)
{
	return static_cast<ModelMeshPart*>(meshPart)->GetIndexBuffer();
}

E3DRSP_Effect E3DRSP_ModelMeshPart_GetShaders(E3DRSP_ModelMeshPart meshPart)
{
	return static_cast<ModelMeshPart*>(meshPart)->GetShaders();
}

void E3DRSP_ModelMeshPart_SetShaders(E3DRSP_ModelMeshPart meshPart, E3DRSP_Effect shaders)
{
	static_cast<ModelMeshPart*>(meshPart)->SetShaders(reinterpret_cast<Effect*>(shaders));
}

E3DRSP_Matrix4x4 E3DRSP_ModelMeshPart_GetTransform(E3DRSP_ModelMeshPart meshPart)
{
	E3DRSP_Matrix4x4 result;
	auto transform = reinterpret_cast<ModelMeshPart*>(meshPart)->Transform;
	memcpy_s(&result, sizeof(float) * 16, &transform, sizeof(Math::Matrix4x4));

	return result;
}

void E3DRSP_ModelMeshPart_SetTransform(E3DRSP_ModelMeshPart meshPart, const E3DRSP_Matrix4x4* transform)
{
	memcpy_s(&static_cast<ModelMeshPart*>(meshPart)->Transform, sizeof(Math::Matrix4x4), transform, sizeof(E3DRSP_Matrix4x4));
}

void E3DRSP_ModelMeshPart_Destroy(E3DRSP_ModelMeshPart meshPart)
{
	assert(meshPart != nullptr);
	delete static_cast<ModelMeshPart*>(meshPart);
}