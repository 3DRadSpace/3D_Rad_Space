#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	class Window;

	namespace Input
	{
		class Mouse
		{
			bool _leftButton;
			bool _middleButton;
			bool _rightButton;

			Math::Point _position;

			float _scrollWheel;

			void _setLeftBtn(bool state);
			void _setRightBtn(bool state);
			void _setPos(const Math::Point& p);
			void _setScrollWheel(float wheel);
		public:
			Mouse() : 
				_leftButton(false),
				_middleButton(false),
				_rightButton(false),
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