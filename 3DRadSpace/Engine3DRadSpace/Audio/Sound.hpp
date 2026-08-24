#pragma once
#include "../Content/IAsset.hpp"
#include "AudioEngine.hpp"
#include "AudioBuffer.hpp"

namespace Engine3DRadSpace::Audio
{
	class SoundInstance;
	/// <summary>
	/// Represents a audio clip.
	/// </summary>
	class E3DRSP_AUDIO_EXPORT Sound : public Content::IAsset
	{
	protected:
		AudioEngine* _audio;
		unsigned int _bufferID;
	
		AudioBuffer _attemptLoading(const std::filesystem::path& path);

		Sound(Internal::AssetUUIDReader dummy);
	public:
		/// <summary>
		/// Constructs an sound from the given audio service and file path.
		/// </summary>
		/// <param name="audio">Audio service</param>
		/// <param name="path">File path to an WAV or OGG sound clip</param>
		Sound(IService* audio, const std::filesystem::path& path);
		
		/// <summary>
		/// Removed copy constructor because the sound buffer is unique and cannot be copied.
		/// </summary>
		/// <param name="">unused</param>
		Sound(const Sound&) = delete;
		/// <summary>
		/// Move constructor. Transfers ownership of the sound buffer to this instance.
		/// </summary>
		/// <param name="snd">The sound to move from</param>
		Sound(Sound&& snd) noexcept;

		/// <summary>
		///	Removed copy assignment operator because the sound buffer is unique and cannot be copied.
		/// </summary>
		/// <param name="from">unused</param>
		/// <returns>unused</returns>
		Sound& operator=(const Sound&) = delete;
		/// <summary>
		///	Move assignement operator. Transfers ownership of the sound buffer to this instance.
		/// </summary>
		/// <param name="snd">The sound to move from</param>
		/// <returns>A reference to this sound instance</returns>
		Sound& operator=(Sound&& snd) noexcept;

		/// <summary>
		/// Returns an unique identifier for the sound asset type.
		/// </summary>
		/// <returns>Identifier for the sound asset type</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		///	Returns an WAV/OGG file filter.
		/// </summary>
		/// <returns>WAV/OGG file filter</returns>
		const char* FileExtension() const noexcept override;
		/// <summary>
		/// Returns the type info of the audio service used to initialize this sound asset.
		/// </summary>
		/// <returns>type info of IAudioEngine</returns>
		std::type_index InitializationService() const noexcept override;

		/// <summary>
		/// Frees the audio buffer associated with this sound instance.
		/// </summary>
		~Sound() override;

		friend class SoundInstance;
		friend struct Internal::AssetUUIDReader;
	};
}