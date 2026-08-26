#include "PostProcessCollection.h"
#include "../../../Graphics/Rendering/PostProcessCollection.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

E3DRSP_PostProcessCollection E3DRSP_CreatePostProcessCollection(E3DRSP_IGraphicsDevice device)
{
	return new PostProcessCollection(static_cast<IGraphicsDevice*>(device));
}

size_t E3DRSP_PostProcessCollection_Count(E3DRSP_PostProcessCollection collection)
{
	return static_cast<PostProcessCollection*>(collection)->Length();
}

void E3DRSP_PostProcessCollection_ApplyAll(E3DRSP_PostProcessCollection collection)
{
	static_cast<PostProcessCollection*>(collection)->ApplyAll();
}

void E3DRSP_PostProcessCollection_EnableAll(E3DRSP_PostProcessCollection collection)
{
	static_cast<PostProcessCollection*>(collection)->EnableAll();
}

void E3DRSP_PostProcessCollection_DisableAll(E3DRSP_PostProcessCollection collection)
{
	static_cast<PostProcessCollection*>(collection)->DisableAll();
}
void E3DRSP_PostProcessCollection_Destroy(E3DRSP_PostProcessCollection collection)
{
	delete static_cast<PostProcessCollection*>(collection);
}