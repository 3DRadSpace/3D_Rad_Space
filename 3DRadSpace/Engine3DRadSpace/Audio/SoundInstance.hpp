#pragma once
#include "Sound.hpp"
#include "AudioSource.hpp"
#include "SoundState.hpp"

namespace Engine3DRadSpace::Audio
{
	/// <summary>
	/// Represents a single instance of a sound.
	/// </summary>
	class E3DRSP_AUDIO_EXPORT SoundInstance
	{
		AudioEngine* _audio;
		unsigned int _sourceID;
		AudioSource _source;
		Sound* _sound;
	public:
		/// <summary>
		/// Constructs a space localized sound instance.
		/// </summary>
		/// <param name="sound">The sound to be played</param>
		/// <param name="source">The audio source</param>
		SoundInstance(Sound* sound, const AudioSource& source);
		/// <summary>
		/// Constructs a sound instance with default audio source settings.
		/// </summary>
		/// <param name="sound">The sound to be played</param>
		explicit SoundInstance(Sound* sound);

		/// <summary>
		/// Move constructor. Transfers ownership of the sound instance to this object.
		/// </summary>
		/// <param name="other">The sound instance to move from</param>
		SoundInstance(SoundInstance&& other) noexcept;
		/// <summary>
		///	Move assignment operator. Transfers ownership of the sound instance to this object.
		/// </summary>
		/// <param name="other">The sound instance to move from</param>
		/// <returns>The sound instance with transferred ownership</returns>
		SoundInstance& operator=(SoundInstance&& other) noexcept;

		/// <summary>
		/// Gets the sound properties associated with this instance.
		/// </summary>
		/// <returns>AudioSource</returns>
		const AudioSource& GetSource() noexcept;
		/// <summary>
		/// Sets the sound properties associated with this instance.
		/// </summary>
		/// <param name="source">The audio source to set</param>
		void SetSource(const AudioSource& source);
		/// <summary>
		/// Gets the state of this sound instance.
		/// </summary>
		/// <returns>Sound state of this</returns>
		SoundState GetState() const noexcept;
		
		/// <summary>
		///	Sets the pitch of this sound instance. Range is [0.5, 2.0]. Default is 1.0.
		/// </summary>
		/// <param name="pitch">The pitch value to set</param>
		void SetPitch(float pitch);
		/// <summary>
		/// Sets the volume of this sound instance. Range is [0.0, 1.0]. Default is 1.0.
		/// </summary>
		/// <param name="gain">volume</param>
		void SetGain(float gain);
		/// <summary>
		/// Sets the maximum volume of this sound instance. Range is [0.0, 1.0]. Default is 1.0.
		/// </summary>
		/// <param name="maxGain">maximum volume</param>
		void SetMaxGain(float maxGain);
		/// <summary>
		/// Sets the minimum volume of this sound instance. Range is [0.0, 1.0]. Default is 0.0.
		/// </summary>
		/// <param name="minGain">minimum volume</param>
		void SetMinGain(float minGain);
		/// <summary>
		/// Sets the 3D position of this sound instance in world space. Default is (0, 0, 0).
		/// </summary>
		/// <param name="pos">the position</param>
		void SetPosition(const Math::Vector3& pos);
		/// <summary>
		/// Sets the velocity of this sound instance, used for Doppler effect calculations. Default is (0, 0, 0).
		/// </summary>
		/// <param name="vel">the velocity</param>
		void SetVelocity(const Math::Vector3& vel);
		/// <summary>
		/// Sets the direction this sound instance is facing, used for directional (cone) sound sources. Default is (0, 0, 0), meaning omnidirectional.
		/// </summary>
		/// <param name="dir">the direction</param>
		void SetDirection(const Math::Vector3& dir);
		/// <summary>
		/// Sets the maximum distance beyond which this sound instance's volume is not attenuated further. Used with the Inverse Clamped Distance Model. Default is FLT_MAX.
		/// </summary>
		/// <param name="distance">maximum distance</param>
		void SetMaxDistance(float distance);
		/// <summary>
		/// Sets the reference distance at which the volume would be unattenuated. Default is 1.0.
		/// </summary>
		/// <param name="refDistance">reference distance</param>
		void SetReferenceDistance(float refDistance);
		/// <summary>
		/// Sets the rolloff factor, controlling how quickly the volume attenuates with distance. Default is 1.0.
		/// </summary>
		/// <param name="rolloff">rolloff factor</param>
		void SetRolloffFactor(float rolloff);
		/// <summary>
		/// Sets the gain applied outside the sound cone's outer angle. Range is [0.0, 1.0]. Default is 0.0.
		/// </summary>
		/// <param name="outerGain">outer cone gain</param>
		void SetConeOuterGain(float outerGain);
		/// <summary>
		/// Sets the inner angle of the sound cone, in degrees, within which the sound is at full volume. Range is [0, 360]. Default is 360.
		/// </summary>
		/// <param name="angle">inner cone angle, in degrees</param>
		void SetConeInnerAngle(float angle);
		/// <summary>
		/// Sets the outer angle of the sound cone, in degrees, beyond which the sound is attenuated to the cone outer gain. Range is [0, 360]. Default is 360.
		/// </summary>
		/// <param name="angle">outer cone angle, in degrees</param>
		void SetConeOuterAngle(float angle);

		/// <summary>
		/// Gets the pitch of this sound instance.
		/// </summary>
		/// <returns>pitch</returns>
		float GetPitch();
		/// <summary>
		/// Gets the volume of this sound instance.
		/// </summary>
		/// <returns>volume</returns>
		float GetGain();
		/// <summary>
		/// Gets the maximum volume of this sound instance.
		/// </summary>
		/// <returns>maximum volume</returns>
		float GetMaxGain();
		/// <summary>
		/// Gets the minimum volume of this sound instance.
		/// </summary>
		/// <returns>minimum volume</returns>
		float GetMinGain();
		/// <summary>
		/// Gets the 3D position of this sound instance in world space.
		/// </summary>
		/// <returns>position</returns>
		Math::Vector3 GetPosition();
		/// <summary>
		/// Gets the velocity of this sound instance.
		/// </summary>
		/// <returns>velocity</returns>
		Math::Vector3 GetVelocity();
		/// <summary>
		/// Gets the direction this sound instance is facing.
		/// </summary>
		/// <returns>direction</returns>
		Math::Vector3 GetDirection();
		/// <summary>
		/// Gets the maximum distance beyond which this sound instance's volume is not attenuated further.
		/// </summary>
		/// <returns>maximum distance</returns>
		float GetMaxDistance();
		/// <summary>
		/// Gets the reference distance at which the volume would be unattenuated.
		/// </summary>
		/// <returns>reference distance</returns>
		float GetReferenceDistance();
		/// <summary>
		/// Gets the rolloff factor.
		/// </summary>
		/// <returns>rolloff factor</returns>
		float GetRolloffFactor();
		/// <summary>
		/// Gets the gain applied outside the sound cone's outer angle.
		/// </summary>
		/// <returns>outer cone gain</returns>
		float GetConeOuterGain();
		/// <summary>
		/// Gets the inner angle of the sound cone, in degrees.
		/// </summary>
		/// <returns>inner cone angle, in degrees</returns>
		float GetConeInnerAngle();
		/// <summary>
		/// Gets the outer angle of the sound cone, in degrees.
		/// </summary>
		/// <returns>outer cone angle, in degrees</returns>
		float GetConeOuterAngle();

		/// <summary>
		/// Gets whether this sound instance is set to loop upon reaching the end of playback.
		/// </summary>
		/// <returns>true if looping is enabled, false otherwise</returns>
		bool IsLooping();
		/// <summary>
		/// Sets whether this sound instance should loop upon reaching the end of playback. Default is false.
		/// </summary>
		/// <param name="looping">true to enable looping, false to disable</param>
		void SetLooping(bool looping);

		/// <summary>
		/// Starts or resumes playback of this sound instance.
		/// </summary>
		/// <param name="dontOverlap">if true, restarts playback from the beginning instead of overlapping with an already playing instance</param>
		void Play(bool dontOverlap = true) const noexcept;
		/// <summary>
		/// Stops playback of this sound instance and resets its playback position.
		/// </summary>
		void Stop() const noexcept;
		/// <summary>
		/// Pauses playback of this sound instance, preserving its current playback position.
		/// </summary>
		void Pause() const noexcept;

		/// <summary>
		/// Deletes the associated OpenAL sound source.
		/// </summary>
		~SoundInstance();
	};
}