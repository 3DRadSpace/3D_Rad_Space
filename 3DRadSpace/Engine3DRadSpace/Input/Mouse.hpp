#pragma once
#include "../Math/Point.hpp"

namespace Engine3DRadSpace
{
	class Window;

	namespace Input
	{
		class DLLEXPORT Mouse
		{
			bool _leftButton;
			bool _middleButton;
			bool _rightButton;

			Math::Point _position;

			float _scrollWheel;
		public:
			Mouse();

			bool LeftButton();
			bool MiddleButton();
			bool RightButton();

			Math::Point Position();

			float ScrollWheel();

			friend class Engine3DRadSpace::Window;
		};
	}
}