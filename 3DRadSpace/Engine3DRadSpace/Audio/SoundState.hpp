#pragma once

namespace Engine3DRadSpace::Audio
{
	/// <summary>
	/// Represents the state of a sound.
	/// </summary>
	enum class SoundState : uint8_t
	{
		/// <summary>
		/// Uninitialized state
		/// </summary>
		Undefined = 0,
		/// <summary>
		/// Sound is stopped and not playing.
		/// </summary>
		Stopped,
		/// <summary>
		/// Sound is currently playing.
		/// </summary>
		Playing,
		/// <summary>
		/// Sound is paused.
		/// </summary>
		Paused,
	};
}