#pragma once

namespace Engine3DRadSpace::Input
{
	/// <summary>
	/// The state of a keyboard key
	/// </summary>
	enum class KeyState : bool
	{
		/// <summary>
		/// Key is not pressed
		/// </summary>
		Up = 0,
		/// <summary>
		/// Key is pressed.
		/// </summary>
		Down = 1
	};
}