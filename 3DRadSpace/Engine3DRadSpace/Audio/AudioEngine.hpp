#pragma once
#include "AudioError.hpp"
#include "IAudioEngine.hpp"
#include "Listener.hpp"

namespace Engine3DRadSpace::Audio
{
	class SoundInstance;
	/// <summary>
	/// OpenAL based audio engine.
	/// </summary>
	class E3DRSP_AUDIO_EXPORT AudioEngine : public IAudioEngine
	{
		void* _audioDevice;
		void* _audioContext;

		bool _hasEAX2support = false;

		void _initializeContext();
	public:
		/// <summary>
		/// Creates an AudioEngine with the default audio device.
		/// </summary>
		/// <remarks>
		/// Copy and move destructors are removed, as this class is expected to have only one instance per Game instance.
		/// </remarks>
		AudioEngine();
		/// <summary>
		/// Creates an AudioEngine with given device name.
		/// </summary>
		/// <param name="deviceName">Audio device name.</param>
		AudioEngine(const std::string& deviceName);

		AudioEngine(const AudioEngine&) = delete;
		AudioEngine(AudioEngine&&) = delete;

		AudioEngine& operator=(const AudioEngine&) = delete;
		AudioEngine& operator=(AudioEngine&&) = delete;

		/// <summary>
		/// Specifies the listener for this audio engine.
		/// </summary>
		class Listener Listener;

		/// <summary>
		/// Returns an list of all available audio devices on the machine.
		/// </summary>
		/// <returns>Vec<string> audio devices</returns>
		static std::vector<std::string> ListAudioDevices();

		/// <summary>
		/// Recreates this AudioEngine with the given audio device name.
		/// </summary>
		void SwitchAudioDevice(const std::string& deviceName) override;

		/// <summary>
		/// Updates the listener.
		/// </summary>
		void Update() noexcept override;

		/// <summary>
		/// Returns the last error.
		/// </summary>
		/// <returns>Last audio error. std::nullopt if no audio errors were raised.</returns>
		std::optional<AudioError> CheckErrors() override;

		~AudioEngine() override;
	};
}