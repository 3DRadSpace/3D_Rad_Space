#pragma once
#include "../Math/Rectangle.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the glyph of a single character in a font.
	/// </summary>
	struct Glyph
	{
		/// <summary>
		/// The character represented by this glyph.
		/// </summary>
		char Character;
		/// <summary>
		/// The size in pixels of the glyph.
		/// </summary>
		Math::Point Size;
		/// <summary>
		/// The offset from the baseline to the top-left of the glyph.
		/// </summary>
		Math::Point Bearing;
		/// <summary>
		/// The horizontal advance to the next glyph.
		/// </summary>
		unsigned Advance;
	};
}