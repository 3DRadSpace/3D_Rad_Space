#pragma once
#include "../../Core/Libs.h"
#include "AudioError.h"
#include "Listener.h"

typedef void* E3DRSP_IAudioEngine;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_IAudioEngine_SwitchAudioDevice(E3DRSP_IAudioEngine audio, const char* deviceName);
	E3DRSP_FFI_EXPORT void E3DRSP_IAudioEngine_Update(E3DRSP_IAudioEngine audio);
	E3DRSP_FFI_EXPORT enum E3DRSP_AudioError E3DRSP_AudioEngine_CheckErrors(E3DRSP_IAudioEngine audio);
	E3DRSP_FFI_EXPORT E3DRSP_Listener E3DRSP_IAudioEngine_GetListener(E3DRSP_IAudioEngine audio);
	E3DRSP_FFI_EXPORT void E3DRSP_IAudioEngine_SetListener(E3DRSP_IAudioEngine audio, const E3DRSP_Listener *listener);
	E3DRSP_FFI_EXPORT void E3DRSP_IAudioEngine_Destroy(E3DRSP_IAudioEngine audio);
#ifdef __cplusplus
}
#endif