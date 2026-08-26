#include "IAudioEngine.h"
#include "../../Audio/IAudioEngine.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;

void E3DRSP_AudioEngine_Update(E3DRSP_IAudioEngine audio)
{
	if (audio == nullptr) return;
	static_cast<IAudioEngine*>(audio)->Update();
}

E3DRSP_AudioError E3DRSP_AudioEngine_CheckErrors(E3DRSP_IAudioEngine audio)
{
	if (audio == nullptr) return E3DRSP_AudioError_None;

	auto err = static_cast<IAudioEngine*>(audio)->CheckErrors();
	if (!err.has_value()) return E3DRSP_AudioError_None;
	else return static_cast<E3DRSP_AudioError>(err.value());
}

void E3DRSP_AudioEngine_SwitchAudioDevice(E3DRSP_IAudioEngine audio, const char* deviceName)
{
	if (audio == nullptr) return;
	static_cast<IAudioEngine*>(audio)->SwitchAudioDevice(deviceName);
}

E3DRSP_Listener E3DRSP_IAudioEngine_GetListener(E3DRSP_IAudioEngine audio)
{
	if (audio == nullptr) return E3DRSP_Listener{};
	return std::bit_cast<E3DRSP_Listener>(static_cast<IAudioEngine*>(audio)->Listener);
}

void E3DRSP_IAudioEngine_SetListener(E3DRSP_IAudioEngine audio, const E3DRSP_Listener* listener)
{
	if (audio == nullptr || listener == nullptr) return;
	static_cast<IAudioEngine*>(audio)->Listener = std::bit_cast<Listener>(*listener);
}

void E3DRSP_AudioEngine_Destroy(E3DRSP_IAudioEngine audio)
{
	assert(audio != nullptr);
	delete static_cast<IAudioEngine*>(audio);
}