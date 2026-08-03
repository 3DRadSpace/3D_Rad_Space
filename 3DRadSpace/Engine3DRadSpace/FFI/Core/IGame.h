#pragma once
#include "../../Core/Libs.h"
#include "IService.h"

typedef void* E3DRSP_IGame;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_IGame_Exit(E3DRSP_IGame game);
	E3DRSP_FFI_EXPORT bool E3DRSP_IGame_WasInitialized(E3DRSP_IGame game);
	E3DRSP_FFI_EXPORT bool E3DRSP_IGame_WasLoaded(E3DRSP_IGame game);
	E3DRSP_FFI_EXPORT void E3DRSP_IGame_AppendScene(E3DRSP_IGame game, const char* path);
	E3DRSP_FFI_EXPORT bool E3DRSP_IGame_IsEditor(E3DRSP_IGame game);

	E3DRSP_FFI_EXPORT void E3DRSP_IGame_Destroy(E3DRSP_IGame game);
#ifdef __cplusplus
}
#endif