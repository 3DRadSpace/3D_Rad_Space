#pragma once
#include "../IObject.hpp"
#include "../../Audio/Sound.hpp"
#include "../../Audio/SoundInstance.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefSound = Content::AssetID<Audio::Sound>;

	class E3DRSP_OBJECTS_IMPL_EXPORT SoundEffect : public IObject
	{
		Audio::Sound* _sound;
		std::unique_ptr<std::string> _path;
		
		std::unique_ptr<Audio::SoundInstance> _instance;

		float _volume;
		float _pitch;
		bool _looping;
	public:
		SoundEffect();

		SoundEffect(
			const std::string& name,
			bool enabled,
			RefSound sound
		);

		SoundEffect(
			const std::string& name,
			bool enabled,
			const std::filesystem::path& path
		);

		SoundEffect(SoundEffect&&) noexcept = default;
		SoundEffect& operator=(SoundEffect&&) noexcept = default;

		RefSound Sound;

		Audio::Sound* GetSound() const noexcept;
		Audio::SoundInstance* GetInstance() const noexcept;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Update() override;

		/// <summary>
		/// Plays the sound.
		/// </summary>
		void Enable() override;
		/// <summary>
		/// Pauses the sound.
		/// </summary>
		void Disable() override;
		/// <summary>
		/// Plays the sound if stopped, and vice-versa.
		/// </summary>
		bool Switch() override;

		Reflection::UUID GetUUID() const noexcept override;

		Gizmos::IGizmo* GetGizmo() const noexcept;

		float GetVolume() const noexcept;
		void SetVolume(float f) noexcept;

		float GetPitch() const noexcept;
		void SetPitch(float p) noexcept;

		bool IsLooping() const noexcept;
		void SetLooping(bool looping) noexcept;

		~SoundEffect() = default;
	};
}

REFL_FWD(SoundEffect)