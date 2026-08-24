#pragma once
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Audio
{
	/// <summary>
	/// Specifies the space position of the audio listener.
	/// </summary>
	struct Listener
	{
		/// <summary>
		/// Overall volume of the listener. 1.0f is full volume, 0.0f is silent.
		/// </summary>
		float Volume = 1.0f;
		/// <summary>
		/// Position in world-space of the listener. Usually the same as the camera position.
		/// </summary>
		Math::Vector3 Position = Math::Vector3::Zero();
		/// <summary>
		/// Velocity of the listener. Used for doppler effects. Usually the same as the camera velocity.
		/// </summary>
		Math::Vector3 Velocity = Math::Vector3::Zero();
		
		/// <summary>
		/// Direction the listener is facing. Usually the same as the camera forward direction.
		/// </summary>	
		Math::Vector3 Direction = Math::Vector3::UnitZ();
		/// <summary>
		/// Normal vector pointing up from the listener. Usually the same as the camera up direction.
		/// </summary>
		Math::Vector3 Normal = Math::Vector3::UnitY();
	
		/// <summary>
		/// Is audio entirely enabled?
		/// </summary>
		bool Enabled = true;
	};
}