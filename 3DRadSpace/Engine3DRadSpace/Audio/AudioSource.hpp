#pragma once
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Audio
{
	/// <summary>
	/// Represents a 3D sound instance.
	/// </summary>
	struct AudioSource
	{
		/// <summary>
		/// Pitch of the sound. Range is [0.5, 2.0]. Default is 1.0.
		/// </summary>
		float Pitch;

		/// <summary>
		/// Volume of the sound. Range is [0.0, 1.0]. Default is 1.0.
		/// </summary>
		float Gain;
		/// <summary>
		/// Max volume of the sound. Range is [0.0, 1.0]. Default is 1.0.
		/// </summary>
		float MaxGain;
		/// Minimum volume of the sound. Range is [0.0, 1.0]. Default is 0.0.
		float MinGain;

		/// <summary>
		/// Position in space of the sound source.
		/// </summary>
		Math::Vector3 Position = Math::Vector3::Zero();
		/// <summary>
		/// Velocity if the object emmiting the sound. Used for doppler effect.
		/// </summary>
		Math::Vector3 Velocity = Math::Vector3::Zero();
		/// <summary>
		/// Normalized direction of the sound source. Used for directional sound.
		/// </summary>
		Math::Vector3 Direction = Math::Vector3::Zero();

		/// <summary>
		/// Maximum distance at which the sound can be heard.
		/// </summary>
		float MaxDistance;
		/// <summary>
		/// Distance at which the sound is at full volume. Beyond this distance, the sound will start to attenuate.
		/// </summary>
		float ReferenceDistance;

		/// <summary>
		/// Describes how quick the sound attenuates as it moves away from the listener. Default is 1.0.
		/// </summary>
		float RolloffFactor;

		/// <summary>
		///
		/// </summary>
		float ConeOuterGain;

		/// <summary>
		/// 
		/// </summary>
		float ConeInnerAngle;

		/// <summary>
		/// 
		/// </summary>
		float ConeOuterAngle;

		/// <summary>
		/// Is the sound looping?
		/// </summary>
		bool Looping;
	};
}