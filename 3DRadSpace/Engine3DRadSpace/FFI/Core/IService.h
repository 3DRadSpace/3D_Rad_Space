#pragma once
#include "../../Core/Libs.h"

typedef void* E3DRSP_IService;
typedef void* E3DRSP_IGame;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_IGame E3DRSP_IService_GetOwner(E3DRSP_IService service);
	E3DRSP_FFI_EXPORT void E3DRSP_IService_Destroy(E3DRSP_IService* service);
#ifdef __cplusplus
}
#endif