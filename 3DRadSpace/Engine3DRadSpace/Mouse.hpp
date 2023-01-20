#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	namespace Input
	{
		struct Mouse
		{
			bool LeftButton;
			bool RightButton;

			Math::Point Position;

			float ScrollWheel;
		};
	}
}