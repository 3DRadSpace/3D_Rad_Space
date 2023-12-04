#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	enum class FlipMode : uint8_t
	{
		None = 0,
		FlipHorizontally = 0b1,
		FlipVertically = 0b10,
		FlipHorizontallyAndVertically = 0b11,
	};

	FlipMode DLLEXPORT operator&(FlipMode a, FlipMode b);
	FlipMode DLLEXPORT operator|(FlipMode a, FlipMode b);
}