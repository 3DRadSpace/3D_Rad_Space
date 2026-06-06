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
		Sound(IService* audio, const std::filesystem::path& path);

		Sound(const Sound&) = delete;
		Sound(Sound&& snd) noexcept;

		Sound& operator=(const Sound&) = delete;
		Sound& operator=(Sound&& snd) noexcept;

		// Inherited via IAsset
		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;
		std::type_index InitializationService() const noexcept override;

		~Sound() override;

		friend class SoundInstance;
		friend struct Internal::AssetUUIDReader;
	};
}