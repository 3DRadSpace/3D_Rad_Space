#pragma once
#include "IRenderer.h"
#include "RenderingManager.h"

typedef void* E3DRSP_NullRenderer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_NullRenderer E3DRSP_NullRenderer_Create(E3DRSP_RenderingManager manager);
#ifdef __cplusplus
}
#endif