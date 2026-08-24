#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents how a image can be flipped.
	/// </summary>
	enum class FlipMode : uint8_t
	{
		/// <summary>
		/// Do not flip the image.
		/// </summary>
		None = 0,
		/// <summary>
		///	Flip around the Y axis (horizontal flip).
		/// </summary>
		FlipHorizontally = 0b1,
		/// <summary>
		/// Flip around the X axis (vertical flip).
		/// </summary>
		FlipVertically = 0b10,
		/// <summary>
		/// Flip around both the X and Y axes (horizontal and vertical flip).
		/// </summary>
		FlipHorizontallyAndVertically = 0b11,
	};

	/// <summary>
	/// Bitwise AND operator between two FlipModes.
	/// </summary>
	/// <param name="a">FlipMode</param>
	/// <param name="b">FlipMode</param>
	/// <returns>a * b</returns>
	FlipMode E3DRSP_GRAPHICS_EXPORT operator&(FlipMode a, FlipMode b);
	/// <summary>
	/// Bitwise OR operator between two FlipModes.
	/// </summary>
	/// <param name="a">FlipMode</param>
	/// <param name="b">FlipMode</param>
	/// <returns>a + b</returns>
	FlipMode E3DRSP_GRAPHICS_EXPORT operator|(FlipMode a, FlipMode b);
}