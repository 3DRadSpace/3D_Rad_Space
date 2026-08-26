#pragma once
#include "../Core/IService.hpp"
#include "AudioError.hpp"
#include "Listener.hpp"

namespace Engine3DRadSpace::Audio
{
	/// <summary>
	/// Instances and handles audio device handles.
	/// </summary>
	class IAudioEngine : public IService
	{
	public:
		/// <summary>
		/// Switches the audio device to the specified device name. If the device name is invalid, it will throw an exception.
		/// </summary>
		/// <param name="deviceName"></param>
		virtual void SwitchAudioDevice(const std::string& deviceName) = 0;
		/// <summary>
		/// Syncronises the listener with the audio engine.
		/// </summary>
		virtual void Update() noexcept = 0;
		/// <summary>
		/// Returns the last audio engine error.
		/// </summary>
		/// <returns>AudioError enum value or std::nullopt otherwise</returns>
		virtual std::optional<AudioError> CheckErrors() = 0;

		/// <summary>
		/// Specifies the listener for this audio engine.
		/// </summary>
		class Listener Listener;

		~IAudioEngine() override = default;
	};
}