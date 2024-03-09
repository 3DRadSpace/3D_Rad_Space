#include "AudioEngine.hpp"
#include "../Logging/Exception.hpp"

#include <AL/al.h>
#include <AL/alc.h>

using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Logging;

AudioEngine::AudioEngine()
{
	//Createa default audio device
	_audioDevice = alcOpenDevice(nullptr);
	if(!_audioDevice)
	{
		throw Exception("Audio device initialization failed!");
	}

	//Create audio scene
	_audioContext = alcCreateContext(_audioDevice, nullptr);
	if(!_audioContext)
	{
		throw Exception("Failed to create audio scene!");
	}

}

std::vector<std::string> AudioEngine::ListAudioDevices()
{
	std::vector<std::string> deviceList;

	auto str = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

	const ALCchar* device = str, * next = str + 1;

	//https://ffainelli.github.io/openal-example/
	while (device && *device != '\0' && next && *next != '\0') {
		deviceList.push_back(device);

		size_t len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}

	return deviceList;
}

void AudioEngine::SetListener(const Math::Vector3& vector)
{
	alListener3f(0, vector.X, vector.Y, vector.Z);
}

void AudioEngine::CreateAudioSource(AudioSource& source)
{

}

AudioEngine::~AudioEngine()
{
	alcDestroyContext(_audioContext);
	alcCloseDevice(_audioDevice);
}
