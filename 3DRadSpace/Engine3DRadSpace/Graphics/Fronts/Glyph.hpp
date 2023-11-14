#pragma once
#include "../../Math/Rectangle.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Engine3DRadSpace::Graphics::Fonts
{
	struct Glyph
	{
		char Character;
		Math::Point   Size;
		Math::Point   Bearing;
		unsigned Advance;
	};
}