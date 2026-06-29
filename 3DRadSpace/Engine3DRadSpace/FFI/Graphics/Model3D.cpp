#include "Model3D.h"
#include "../../Graphics/Model3D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_Model3D EDRSP_Model3D_Create(E3DRSP_IGraphicsDevice device, const char* path)
{
	return new Model3D(static_cast<IGraphicsDevice*>(device), std::filesystem::path(path));
}

void EDRSP_Model3D_Draw(E3DRSP_Model3D model)
{
	static_cast<Model3D*>(model)->Draw();
}

void EDRSP_Model3D_Draw2(E3DRSP_Model3D model, const E3DRSP_Matrix4x4* transform)
{
	static_cast<Model3D*>(model)->Draw(*reinterpret_cast<const Math::Matrix4x4*>(transform));
}

void EDRSP_Model3D_DrawEffect(E3DRSP_Model3D model, E3DRSP_Effect effect)
{
	static_cast<Model3D*>(model)->DrawEffect(static_cast<Effect*>(effect));
}

void EDRSP_Model3D_DrawEffect2(E3DRSP_Model3D model, E3DRSP_Effect effect, const E3DRSP_Matrix4x4* transform)
{
	static_cast<Model3D*>(model)->DrawEffect(static_cast<Effect*>(effect), *reinterpret_cast<const Math::Matrix4x4*>(transform));
}

size_t EDRSP_Model3D_NumMeshes(E3DRSP_Model3D model)
{
	return static_cast<Model3D*>(model)->NumMeshes();
}

E3DRSP_ModelMesh EDRSP_Model3D_GetMesh(E3DRSP_Model3D model, size_t index)
{
	return static_cast<E3DRSP_ModelMesh>(static_cast<Model3D*>(model)->operator[](index));
}

E3DRSP_BoundingBox EDRSP_Model3D_GetBoundingBox(E3DRSP_Model3D model)
{
	BoundingBox b = static_cast<Model3D*>(model)->GetBoundingBox();

	return E3DRSP_BoundingBox{
		{b.Position.X, b.Position.Y, b.Position.Z},
		{b.Scale.X, b.Scale.Y, b.Scale.Z}
	};
}

E3DRSP_BoundingSphere EDRSP_Model3D_GetBoundingSphere(E3DRSP_Model3D model)
{
	BoundingSphere s = static_cast<Model3D*>(model)->GetBoundingSphere();

	return E3DRSP_BoundingSphere{
		{s.Center.X, s.Center.Y, s.Center.Z},
		s.Radius
	};
}

void EDRSP_Model3D_SetShader(E3DRSP_Model3D model, E3DRSP_Effect effect)
{
	static_cast<Model3D*>(model)->SetShader(static_cast<Effect*>(effect));
}

void EDRSP_Model3D_SetShaders(E3DRSP_Model3D model, E3DRSP_Effect* effects, size_t numEffects)
{
	std::vector<Effect*> effectVec;
	effectVec.reserve(numEffects);

	for(size_t i = 0; i < numEffects; i++)
	{
		effectVec.push_back(static_cast<Effect*>(effects[i]));
	}
	static_cast<Model3D*>(model)->SetShaders(effectVec);
}

void EDRSP_Model3D_SetTransform(E3DRSP_Model3D model, const E3DRSP_Matrix4x4* matrix4x4)
{
	static_cast<Model3D*>(model)->SetTransform(*reinterpret_cast<const Math::Matrix4x4*>(matrix4x4));
}

void EDRSP_Model3D_Destroy(E3DRSP_Model3D model)
{
	delete static_cast<Model3D*>(model);
}