#include "ModelMesh.h"
#include "../../Graphics/ModelMesh.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_ModelMesh E3DRSP_ModelMesh_Create(E3DRSP_ModelMeshPart* parts, size_t numParts)
{
	return reinterpret_cast<E3DRSP_ModelMesh>(new ModelMesh(reinterpret_cast<ModelMeshPart*>(parts), numParts));
}

void E3DRSP_ModelMesh_AddMeshPart(E3DRSP_ModelMesh mesh, E3DRSP_ModelMeshPart part)
{
	reinterpret_cast<ModelMesh*>(mesh)->AddMeshPart(std::make_unique<ModelMeshPart>(std::move(*reinterpret_cast<ModelMeshPart*>(part))));
}

E3DRSP_ModelMeshPart E3DRSP_ModelMesh_GetMeshPart(E3DRSP_ModelMesh mesh, unsigned index)
{
	return reinterpret_cast<E3DRSP_ModelMeshPart>(reinterpret_cast<ModelMesh*>(mesh)->operator[](index));
}

size_t E3DRSP_ModelMesh_NumMeshParts(E3DRSP_ModelMesh mesh)
{
	return reinterpret_cast<ModelMesh*>(mesh)->NumMeshParts();
}

void E3DRSP_ModelMesh_Draw(E3DRSP_ModelMesh mesh)
{
	reinterpret_cast<ModelMesh*>(mesh)->Draw();
}

E3DRSP_BoundingBox E3DRSP_ModelMesh_GetBoundingBox(E3DRSP_ModelMesh mesh)
{
	BoundingBox box = reinterpret_cast<ModelMesh*>(mesh)->GetBoundingBox();
	return E3DRSP_BoundingBox{
		E3DRSP_Vector3{ box.Position.X, box.Position.Y, box.Position.Z },
		E3DRSP_Vector3{ box.Scale.X, box.Scale.Y, box.Scale.Z }
	};
}

E3DRSP_BoundingSphere E3DRSP_ModelMesh_GetBoundingSphere(E3DRSP_ModelMesh mesh)
{
	BoundingSphere sphere = reinterpret_cast<ModelMesh*>(mesh)->GetBoundingSphere();
	return E3DRSP_BoundingSphere{
		E3DRSP_Vector3{ sphere.Center.X, sphere.Center.Y, sphere.Center.Z },
		sphere.Radius
	};
}

void E3DRSP_ModelMesh_Destroy(E3DRSP_ModelMesh mesh)
{
	delete reinterpret_cast<ModelMesh*>(mesh);
}