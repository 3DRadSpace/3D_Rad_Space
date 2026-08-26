#pragma once
#include "../IGraphicsDevice.h"

typedef void* E3DRSP_PostProcessCollection;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_PostProcessCollection E3DRSP_CreatePostProcessCollection(E3DRSP_IGraphicsDevice device);

	E3DRSP_FFI_EXPORT size_t E3DRSP_PostProcessCollection_Count(E3DRSP_PostProcessCollection collection);
	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessCollection_ApplyAll(E3DRSP_PostProcessCollection collection);
	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessCollection_EnableAll(E3DRSP_PostProcessCollection collection);
	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessCollection_DisableAll(E3DRSP_PostProcessCollection collection);
	E3DRSP_FFI_EXPORT void E3DRSP_PostProcessCollection_Destroy(E3DRSP_PostProcessCollection collection);
#ifdef __cplusplus
}
#endif