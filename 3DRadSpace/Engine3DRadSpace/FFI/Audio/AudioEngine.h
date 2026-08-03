#pragma once
#include "IAudioEngine.h"
#include "AudioError.h"

#ifdef __cplusplus
extern "C"
{
#endif
	/// <summary>
	/// Creates an audio engine, with default device.
	/// </summary>
	/// <remarks>
	/// Any AudioEngine instance will need to be freed using E3DRSP_AudioEngine_Destroy.
	/// </remarks>
	/// <returns>Pointer to a AudioEngine instance.</returns>
	E3DRSP_FFI_EXPORT E3DRSP_IAudioEngine E3DRSP_AudioEngine_Create();
	/// <summary>
	/// Creates an audio engine, with specfied device name.
	/// </summary>
	/// <param name="deviceName">Device name.</param>
	/// <returns>AudioEngine instance</returns>
	E3DRSP_FFI_EXPORT E3DRSP_IAudioEngine E3DRSP_AudioEngine_Create1(const char* deviceName);
	/// <summary>
	/// Lists audio devices.
	/// </summary>
	/// <remarks>
	/// Any AudioEngine instance will need to be freed using E3DRSP_AudioEngine_Destroy.
	/// </remarks>
	/// <returns>A list of strings that's dynamically allocated. Each string should be freed first, then free the list.</returns>
	E3DRSP_FFI_EXPORT char** E3DRSP_AudioEngine_ListAudioDevices();
#ifdef __cplusplus
}
#endif