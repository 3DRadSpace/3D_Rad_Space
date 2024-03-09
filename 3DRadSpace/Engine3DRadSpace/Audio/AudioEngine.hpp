#pragma once
#include "AudioSource.hpp"

struct ALCdevice;
struct ALCcontext;
namespace Engine3DRadSpace::Audio
{
	class DLLEXPORT AudioEngine
	{
		ALCdevice *_audioDevice;
		ALCcontext* _audioContext;
	public:
		AudioEngine();

		AudioEngine(AudioEngine&) = delete;
		AudioEngine(AudioEngine&&) = delete;

		AudioEngine& operator=(AudioEngine&) = delete;
		AudioEngine& operator=(AudioEngine&&) = delete;

		std::vector<std::string> ListAudioDevices();

		void SetListener(const Math::Vector3& vector);
		void CreateAudioSource(AudioSource& source);

		~AudioEngine();
	};
}