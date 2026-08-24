#pragma once

namespace Engine3DRadSpace::Input
{
	/// <summary>
	/// Represents the state of a button (pressed or released).
	/// </summary>
	enum class ButtonState : bool
	{
		/// <summary>
		///	The button is released(not pressed).
		/// </summary>
		Released = 0,
		/// <summary>
		/// The button is pressed.
		/// </summary>
		Pressed = 1
	};
}