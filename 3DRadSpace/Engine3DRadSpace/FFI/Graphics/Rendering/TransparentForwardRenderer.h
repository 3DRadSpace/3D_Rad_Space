#pragma once
#include "IRenderer.h"
#include "RenderingManager.h"

typedef void* E3DRSP_TransparentForwardRenderer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_TransparentForwardRenderer E3DRSP_TransparentForwardRenderer_Create(E3DRSP_RenderingManager manager);
#ifdef __cplusplus
}
#endif