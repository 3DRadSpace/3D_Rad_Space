#pragma once
#include "../Math/Point.hpp"
#include "ButtonState.hpp"

namespace Engine3DRadSpace
{
	namespace Native
	{
		class Window;
	}

	namespace Input
	{
		/// <summary>
		/// Represents the mouse input state.
		/// </summary>
		class E3DRSP_INPUT_EXPORT Mouse
		{
			ButtonState _leftButton;
			ButtonState _middleButton;
			ButtonState _rightButton;

			Math::Point _position;

			float _scrollWheel;
		public:
			/// <summary>
			/// Constructs a new Mouse instance with default values.
			/// </summary>
			Mouse();

			/// <summary>
			///	Gets the button state of the left mouse button.
			/// </summary>
			/// <returns>Button state of the left mouse button</returns>
			ButtonState LeftButton() const noexcept;
			/// <summary>
			///	Gets the button state of the middle mouse button.
			/// </summary>
			/// <returns>Button state of the middle mouse button</returns>
			ButtonState MiddleButton() const noexcept;
			/// <summary>
			///	Gets the button state of the right mouse button.
			/// </summary>
			/// <returns>Button state of the right mouse button</returns>
			ButtonState RightButton() const noexcept;

			/// <summary>
			///	Gets the current position of the mouse cursor.
			/// </summary>
			/// <returns>Current position of the mouse cursor</returns>
			Math::Point Position() const noexcept;

			/// <summary>
			///	Gets an integer value representing the amount of scroll wheel movement.
			/// </summary>
			/// <returns></returns>
			float ScrollWheel() const noexcept;

			friend class Native::Window;
		};
	}
}