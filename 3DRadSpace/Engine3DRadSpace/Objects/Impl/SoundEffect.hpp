#pragma once
#include "../IObject.hpp"
#include "../../Audio/Sound.hpp"
#include "../../Audio/SoundInstance.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefSound = Content::AssetID<Audio::Sound>;
	/// <summary>
	/// Represents an 2D sound effect that can be played in the scene.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT SoundEffect : public IObject
	{
		Audio::Sound* _sound;
		std::unique_ptr<std::string> _path;
		
		std::unique_ptr<Audio::SoundInstance> _instance;

		float _volume;
		float _pitch;
		bool _looping;
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		SoundEffect();
		/// <summary>
		/// Constructs a sound effect from an numerical asset identifier.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Is this object enabled?</param>
		/// <param name="sound">Numerical asset identifier for the sound</param>
		SoundEffect(
			const std::string& name,
			bool enabled,
			RefSound sound
		);
		/// <summary>
		///	Constructs an sound effect from an file path.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Is this object enabled?</param>
		/// <param name="path">File path to the sound(OGG or WAV)</param>
		SoundEffect(
			const std::string& name,
			bool enabled,
			const std::filesystem::path& path
		);

		SoundEffect(SoundEffect&&) noexcept = default;
		SoundEffect& operator=(SoundEffect&&) noexcept = default;
		/// <summary>
		/// Numerical reference to the sound asset used by this object.
		/// </summary>
		RefSound Sound;
		/// <summary>
		/// Gets the underlying sound asset used by this object.
		/// </summary>
		/// <returns>Pointer to the underlying sound asset</returns>
		Audio::Sound* GetSound() const noexcept;
		/// <summary>
		/// Gets the underlying sound instance used by this object.
		/// </summary>
		/// <returns>Pointer to the underlying sound instance</returns>
		Audio::SoundInstance* GetInstance() const noexcept;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Loads the sound asset.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads a sound from an specified path.
		/// </summary>
		/// <param name="path">WAV or OGG file</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Does nothing.
		/// </summary>
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
		/// <summary>
		/// Gets the UUID of the SoundEffect type.
		/// </summary>
		/// <returns>{4C9A4E2A-99DC-4E61-B5CB-3D75B569531F}</returns>
		Reflection::UUID GetUUID() const noexcept override;

		Gizmos::IGizmo* GetGizmo() const noexcept;
		/// <summary>
		/// Gets the gain of the sound effect.
		/// </summary>
		/// <returns>Volume</returns>
		float GetVolume() const noexcept;
		/// <summary>
		/// Sets the gain of the sound effect. Range is [0.0, 1.0]. Default is 1.0.
		/// </summary>
		/// <param name="f">Volume</param>
		void SetVolume(float f) noexcept;
		/// <summary>
		///	Gets the pitch of the sound effect.
		/// </summary>
		/// <returns>Pitch</returns>
		float GetPitch() const noexcept;
		/// <summary>
		/// Sets the pitch of the sound effect. Default is 1.0. Range is [0.5, 2.0]. Values outside this range may cause audio distortion.
		/// </summary>
		/// <param name="p"></param>
		void SetPitch(float p) noexcept;
		/// <summary>
		/// Gets whether the sound effect is looping.
		/// </summary>
		/// <returns>True if the sound effect is looping, false otherwise</returns>	
		bool IsLooping() const noexcept;
		/// <summary>
		/// Sets whether the sound effect is looping.
		/// </summary>
		/// <param name="looping">True to make the sound effect loop, false otherwise</param>
		void SetLooping(bool looping) noexcept;

		~SoundEffect() = default;
	};
}

REFL_FWD(SoundEffect)