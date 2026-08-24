#pragma once
#include "SoundEffect.hpp"
#include "../IObject3D.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a 3D positional sound source that can be placed in the scene, using OpenAL-Soft's 3D audio spatialization.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT SoundSource : public IObject3D
	{
		SoundEffect _underlying;

		float _volume;
		float _pitch;
		bool _looping;

		Math::Vector3 _velocity;
		Math::Vector3 _direction;

		float _maxDistance;
		float _referenceDistance;
		float _rolloffFactor;
		float _coneInnerAngle;
		float _coneOuterAngle;
		float _coneOuterGain;
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		SoundSource();

		/// <summary>
		/// Constructs a 3D sound source from a numerical asset identifier.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Is this object enabled?</param>
		/// <param name="sound">Numerical asset identifier for the sound</param>
		/// <param name="position">Initial 3D position of the sound source</param>
		SoundSource(
			const std::string &name,
			bool enabled,
			RefSound sound,
			const Math::Vector3 &position
		);

		/// <summary>
		/// Constructs a 3D sound source from a file path.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Is this object enabled?</param>
		/// <param name="soundFile">File path to the sound(OGG or WAV)</param>
		/// <param name="position">Initial 3D position of the sound source</param>
		SoundSource(
			const std::string &name,
			bool enabled,
			const std::filesystem::path& soundFile,
			const Math::Vector3 &position
		);

		SoundSource(SoundSource&&) noexcept = default;
		SoundSource& operator=(SoundSource&&) noexcept = default;

		/// <summary>
		/// Does nothing, as sound sources are not rendered visually.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Tests for intersections with the sound source's bounding volume.
		/// </summary>
		/// <param name="r">Ray to test against</param>
		/// <returns>Distance to the intersection point, or a negative value if there is no intersection</returns>
		float Intersects(const Math::Ray &r) const override;

		/// <summary>
		/// Gets the UUID of the SoundSource type.
		/// </summary>
		/// <returns>{...}</returns>
		Reflection::UUID GetUUID() const noexcept override;

		/// <summary>
		/// Applies the initial 3D audio parameters (position, velocity, direction, distance/cone attenuation) to the underlying OpenAL-Soft source.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Loads the sound asset.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads a sound from a specified path.
		/// </summary>
		/// <param name="path">WAV or OGG file</param>
		void Load(const std::filesystem::path & path) override;
		/// <summary>
		/// Updates the 3D position, velocity and direction of the sound source.
		/// </summary>
		void Update() override;
		Objects::Gizmos::IGizmo *GetGizmo() const noexcept override;

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
		/// Gets the underlying sound asset used by this object.
		/// </summary>
		/// <returns>Numerical reference to the sound asset</returns>
		RefSound GetSoundAsset() const noexcept;
		/// <summary>
		/// Sets the underlying sound asset used by this object.
		/// </summary>
		/// <param name="sound">Numerical reference to the sound asset</param>
		void SetSoundAsset(RefSound sound) noexcept;

		/// <summary>
		/// Gets the gain of the sound source.
		/// </summary>
		/// <returns>Volume</returns>
		float GetVolume() const noexcept;
		/// <summary>
		/// Sets the gain of the sound source. Range is [0.0, 1.0]. Default is 1.0.
		/// </summary>
		/// <param name="volume">Volume</param>
		void SetVolume(float volume) noexcept;

		/// <summary>
		/// Gets the pitch of the sound source.
		/// </summary>
		/// <returns>Pitch</returns>
		float GetPitch() const noexcept;
		/// <summary>
		/// Sets the pitch of the sound source. Default is 1.0. Range is [0.5, 2.0]. Values outside this range may cause audio distortion.
		/// </summary>
		/// <param name="pitch">Pitch</param>
		void SetPitch(float pitch) noexcept;

		/// <summary>
		/// Gets whether the sound source is looping.
		/// </summary>
		/// <returns>True if the sound source is looping, false otherwise</returns>
		bool IsLooping() const noexcept;
		/// <summary>
		/// Sets whether the sound source is looping.
		/// </summary>
		/// <param name="looping">True to make the sound source loop, false otherwise</param>
		void SetLooping(bool looping) noexcept;

		/// <summary>
		/// Gets the velocity of the sound source, used by OpenAL-Soft to compute the Doppler effect.
		/// </summary>
		/// <returns>Velocity vector</returns>
		Math::Vector3 GetVelocity() const noexcept;
		/// <summary>
		/// Sets the velocity of the sound source, used by OpenAL-Soft to compute the Doppler effect.
		/// </summary>
		/// <param name="velocity">Velocity vector</param>
		void SetVelocity(const Math::Vector3& velocity) noexcept;

		/// <summary>
		/// Gets the direction the sound source is facing, used for directional (cone-shaped) sound emission.
		/// </summary>
		/// <returns>Direction vector</returns>
		Math::Vector3 GetDirection() const noexcept;
		/// <summary>
		/// Sets the direction the sound source is facing, used for directional (cone-shaped) sound emission.
		/// </summary>
		/// <param name="direction">Direction vector</param>
		void SetDirection(const Math::Vector3& direction) noexcept;

		/// <summary>
		/// Gets the maximum distance beyond which the sound source is no longer attenuated.
		/// </summary>
		/// <returns>Maximum distance</returns>
		float GetMaxDistance() const noexcept;
		/// <summary>
		/// Sets the maximum distance beyond which the sound source is no longer attenuated. Default is the maximum representable float value.
		/// </summary>
		/// <param name="dst">Maximum distance</param>
		void SetMaxDistance(float dst) noexcept;

		/// <summary>
		/// Gets the reference distance at which the volume would be at its unattenuated value.
		/// </summary>
		/// <returns>Reference distance</returns>
		float GetReferenceDistance() const noexcept;
		/// <summary>
		/// Sets the reference distance at which the volume would be at its unattenuated value. Default is 1.0.
		/// </summary>
		/// <param name="refDst">Reference distance</param>
		void SetReferenceDistance(float refDst) noexcept;

		/// <summary>
		/// Gets the rolloff factor, controlling how quickly the sound attenuates with distance.
		/// </summary>
		/// <returns>Rolloff factor</returns>
		float GetRolloffFactor() const noexcept;
		/// <summary>
		/// Sets the rolloff factor, controlling how quickly the sound attenuates with distance. Default is 1.0.
		/// </summary>
		/// <param name="rollOff">Rolloff factor</param>
		void SetRolloffFactor(float rollOff) noexcept;

		/// <summary>
		/// Gets the inner angle, in degrees, of the sound cone within which the sound is emitted at full volume.
		/// </summary>
		/// <returns>Cone inner angle, in degrees</returns>
		float GetConeInnerAngle() const noexcept;
		/// <summary>
		/// Sets the inner angle, in degrees, of the sound cone within which the sound is emitted at full volume. Default is 360.0 (omnidirectional).
		/// </summary>
		/// <param name="innerAngle">Cone inner angle, in degrees</param>
		void SetConeInnerAngle(float innerAngle) noexcept;

		/// <summary>
		/// Gets the outer angle, in degrees, of the sound cone outside of which the sound is attenuated by the cone outer gain.
		/// </summary>
		/// <returns>Cone outer angle, in degrees</returns>
		float GetConeOuterAngle() const noexcept;
		/// <summary>
		/// Sets the outer angle, in degrees, of the sound cone outside of which the sound is attenuated by the cone outer gain. Default is 360.0 (omnidirectional).
		/// </summary>
		/// <param name="outerAngle">Cone outer angle, in degrees</param>
		void SetConeOuterAngle(float outerAngle) noexcept;

		/// <summary>
		/// Gets the gain applied to the sound outside the outer cone angle.
		/// </summary>
		/// <returns>Cone outer gain</returns>
		float GetConeOuterGain() const noexcept;
		/// <summary>
		/// Sets the gain applied to the sound outside the outer cone angle. Default is 0.0.
		/// </summary>
		/// <param name="outerGain">Cone outer gain</param>
		void SetConeOuterGain(float outerGain) noexcept;

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

		~SoundSource() = default;
	};
}

REFL_FWD(SoundSource)