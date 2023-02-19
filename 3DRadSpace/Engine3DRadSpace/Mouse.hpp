#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	class Window;

	namespace Input
	{
		class Mouse
		{
			bool leftButton;
			bool middleButton;
			bool rightButton;

			Math::Point _position;

			float _scrollWheel;
		public:
			Mouse() : 
				leftButton(false),
				middleButton(false),
				rightButton(false),
				_position(),
				_scrollWheel(0) {};

			bool LeftButton();
			bool MiddleButton();
			bool RightButton();

			Math::Point Position();

			float ScrollWheel();

			friend class Engine3DRadSpace::Window;
		};
	}
}