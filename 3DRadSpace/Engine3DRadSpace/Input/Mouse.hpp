#pragma once
#include "../Math/Point.hpp"

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

			Math::Point position;

			float scrollWheel;
		public:
			Mouse() : 
				leftButton(false),
				middleButton(false),
				rightButton(false),
				position(),
				scrollWheel(0) {};

			bool LeftButton();
			bool MiddleButton();
			bool RightButton();

			Math::Point Position();

			float ScrollWheel();

			friend class Engine3DRadSpace::Window;
		};
	}
}