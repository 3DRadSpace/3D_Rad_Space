#pragma once
#include "../Math/Vector3.hpp"

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

		void SetListener(const Math::Vector3& vector);

		~AudioEngine();
	};
}