#pragma once
#include "../Core/Libs.h"
#include "Math/Ray.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"

typedef void* E3DRSP_Game;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_Game E3DRSP_Game_Create(const char* title, size_t width, size_t height);
	
	E3DRSP_FFI_EXPORT void E3DRSP_Game_Run(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void E3DRSP_Game_RunOneFrame(E3DRSP_Game game);

	E3DRSP_FFI_EXPORT E3DRSP_Ray E3DRSP_Game_GetMouseRay(
		E3DRSP_Game game,
		E3DRSP_Vector2 mousePos,
		const E3DRSP_Matrix4x4* view,
		const E3DRSP_Matrix4x4* projection
	);

	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetSpriteBatch(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetIGraphicsDevice(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetPostProcessCollection(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetIPhysicsEngine(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetRenderingManager(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetObjectList(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetContentManager(E3DRSP_Game game);
	E3DRSP_FFI_EXPORT void* E3DRSP_Game_GetCameraProvider(E3DRSP_Game game);
#ifdef __cplusplus
}
#endif
