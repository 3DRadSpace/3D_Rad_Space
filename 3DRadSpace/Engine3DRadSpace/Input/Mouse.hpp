#pragma once
#include "../Math/Point.hpp"
#include "ButtonState.hpp"

namespace Engine3DRadSpace
{
	class Window;

	namespace Input
	{
		class DLLEXPORT Mouse
		{
			ButtonState _leftButton;
			ButtonState _middleButton;
			ButtonState _rightButton;

			Math::Point _position;

			float _scrollWheel;
		public:
			Mouse();

			ButtonState LeftButton();
			ButtonState MiddleButton();
			ButtonState RightButton();

			Math::Point Position();

			float ScrollWheel();

			friend class Window;
		};
	}
}