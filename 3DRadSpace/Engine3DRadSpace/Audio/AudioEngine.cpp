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

void AudioEngine::SetListener(const Math::Vector3& vector)
{
	alListener3f(0, vector.X, vector.Y, vector.Z);
}

AudioEngine::~AudioEngine()
{
	alcDestroyContext(_audioContext);
	alcCloseDevice(_audioDevice);
}
