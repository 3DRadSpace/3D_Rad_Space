#pragma once
#include "../../Core/Libs.h"

typedef void* E3DRSP_IInitializable;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_IInitializable_Initialize(E3DRSP_IInitializable instance);
	E3DRSP_FFI_EXPORT void E3DRSP_IInitializable_Destroy(E3DRSP_IInitializable instance);
#ifdef __cplusplus
}
#endif