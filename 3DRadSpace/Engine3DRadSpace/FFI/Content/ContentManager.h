#pragma once
#include "IAsset.h"
#include "../Reflection/UUID.h"

typedef void* E3DRSP_ContentManager;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_IAsset E3DRSP_ContentManager_Load(
		E3DRSP_ContentManager content, 
		const E3DRSP_UUID* uuid, 
		const char* path,
		unsigned* id
	);

	E3DRSP_FFI_EXPORT void E3DRSP_ContentManager_Reload(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_FFI_EXPORT E3DRSP_IAsset E3DRSP_ContentManager_At(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_FFI_EXPORT const char* E3DRSP_ContentManager_GetAssetPath(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_FFI_EXPORT E3DRSP_UUID E3DRSP_ContentManager_GetAssetType(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_FFI_EXPORT const char* E3DRSP_ContentManager_GetAssetName(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_FFI_EXPORT void E3DRSP_ContentManager_Remove(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_FFI_EXPORT void E3DRSP_ContentManager_Clear(E3DRSP_ContentManager content);
	E3DRSP_FFI_EXPORT size_t E3DRSP_ContentManager_Count(E3DRSP_ContentManager content);
#ifdef __cplusplus
}
#endif