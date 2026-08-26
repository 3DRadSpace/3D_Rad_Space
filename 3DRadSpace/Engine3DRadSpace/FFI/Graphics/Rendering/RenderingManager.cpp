#include "RenderingManager.h"
#include "../../../Graphics/Rendering/RenderingManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

E3DRSP_RenderingManager E3DRSP_RenderingManager_Create(E3DRSP_IGraphicsDevice device)
{
	return new RenderingManager(static_cast<IGraphicsDevice*>(device));
}

void E3DRSP_RenderingManager_Add(E3DRSP_RenderingManager manager, E3DRSP_IRenderer renderer)
{
	static_cast<RenderingManager*>(manager)->Add(std::unique_ptr<IRenderer>(static_cast<IRenderer*>(renderer)));
}

E3DRSP_IRenderer E3DRSP_RenderingManager_At(E3DRSP_RenderingManager manager, size_t index)
{
	return static_cast<RenderingManager*>(manager)->operator[](index);
}

size_t E3DRSP_RenderingManager_NumPasses(E3DRSP_RenderingManager manager)
{
	return static_cast<RenderingManager*>(manager)->NumPasses();
}

void E3DRSP_RenderingManager_Remove(E3DRSP_RenderingManager manager, size_t index)
{
	static_cast<RenderingManager*>(manager)->Remove(index);
}

void E3DRSP_RenderingManager_Clear(E3DRSP_RenderingManager manager)
{
	static_cast<RenderingManager*>(manager)->Clear();
}

void E3DRSP_RenderingManager_Draw(E3DRSP_RenderingManager manager, E3DRSP_Model3D model, E3DRSP_RenderPassType passType)
{
	static_cast<RenderingManager*>(manager)->Draw(static_cast<Model3D*>(model), static_cast<RenderPassType>(passType));
}

void E3DRSP_RenderingManager_Draw2(E3DRSP_RenderingManager manager, E3DRSP_ModelMeshPart model, E3DRSP_RenderPassType passType)
{
	static_cast<RenderingManager*>(manager)->Draw(static_cast<ModelMeshPart*>(model), static_cast<RenderPassType>(passType));
}

void E3DRSP_RenderingManager_Execute(E3DRSP_RenderingManager manager)
{
	static_cast<RenderingManager*>(manager)->Execute();
}

E3DRSP_RenderingManager E3DRSP_RenderingManager_CreateForward(E3DRSP_IGraphicsDevice device)
{
	return RenderingManager::CreateForward(static_cast<IGraphicsDevice*>(device)).release();
}

E3DRSP_RenderingManager E3DRSP_RenderingManager_CreateTrivial(E3DRSP_IGraphicsDevice device)
{
	return RenderingManager::CreateTrivial(static_cast<IGraphicsDevice*>(device)).release();
}

E3DRSP_RenderingManager E3DRSP_RenderingManager_CreateNull(E3DRSP_IGraphicsDevice device)
{
	return RenderingManager::CreateNull(static_cast<IGraphicsDevice*>(device)).release();
}

E3DRSP_DirectionalLight E3DRSP_RenderingManager_GetDirectionalLight(E3DRSP_RenderingManager manager)
{
	return std::bit_cast<E3DRSP_DirectionalLight>(static_cast<RenderingManager*>(manager)->MainLight);
}
void E3DRSP_RenderingManager_SetDirectionalLight(E3DRSP_RenderingManager manager, const E3DRSP_DirectionalLight *light)
{
	static_cast<RenderingManager*>(manager)->MainLight = std::bit_cast<DirectionalLight>(*light);
}

E3DRSP_IGraphicsDevice E3DRSP_RenderingManager_GetGraphicsDevice(E3DRSP_RenderingManager manager)
{
	return static_cast<RenderingManager*>(manager)->GetDevice();
}

void E3DRSP_RenderingManager_Destroy(E3DRSP_RenderingManager manager)
{
	delete static_cast<RenderingManager*>(manager);
}