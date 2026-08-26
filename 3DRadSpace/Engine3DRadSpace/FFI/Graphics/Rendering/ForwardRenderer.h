#pragma once
#include "IRenderer.h"
#include "RenderingManager.h"

typedef void* E3DRSP_ForwardRenderer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_ForwardRenderer E3DRSP_ForwardRenderer_Create(E3DRSP_RenderingManager manager);
#ifdef __cplusplus
}
#endif