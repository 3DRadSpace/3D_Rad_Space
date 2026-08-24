#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents a size in 2D space with width (X) and height (Y).
	/// </summary>
	struct Size
	{
		/// <summary>
		/// The X component of the size, representing the width.
		/// </summary>
		size_t X;
		/// <summary>
		/// The y component of the size, representing the height.
		/// </summary>
		size_t Y;
	};
}