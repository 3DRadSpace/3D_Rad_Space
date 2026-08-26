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
		/// <summary>
		/// Minimum volume of the sound. Range is [0.0, 1.0]. Default is 0.0.
		/// </summary>
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
		/// Gain multiplier applied to the sound when the listener is outside the outer cone angle. Range is [0.0, 1.0]. Default is 0.0.
		/// </summary>
		float ConeOuterGain;

		/// <summary>
		/// Angle, in degrees, of the inner sound cone within which the sound is heard at full gain. Range is [0, 360]. Default is 360.
		/// </summary>
		float ConeInnerAngle;

		/// <summary>
		/// Angle, in degrees, of the outer sound cone beyond which the sound is attenuated to ConeOuterGain. Range is [0, 360]. Default is 360.
		/// </summary>
		float ConeOuterAngle;

		/// <summary>
		/// Is the sound looping?
		/// </summary>
		bool Looping;
	};
}