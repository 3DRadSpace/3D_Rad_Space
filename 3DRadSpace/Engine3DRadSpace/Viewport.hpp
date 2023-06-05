#pragma once
#include "Libs.hpp"
#include "Math/Rectangle.hpp"

namespace Engine3DRadSpace
{
	struct Viewport
	{
		Viewport(Math::RectangleF r, float mind, float maxd) : ScreenRectangle(r), MinDepth(mind), MaxDepth(maxd) {};

		Math::RectangleF ScreenRectangle;

		float MinDepth;
		float MaxDepth;
	};
}

