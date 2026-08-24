#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Specifies the stencil buffer operations.
	/// </summary>
	enum class StencilOperation : int
	{
		/// <summary>
		///	Keep the current value in the stencil buffer.
		/// </summary>
		Keep = 1,
		/// <summary>
		/// Set the value in the stencil buffer to zero.
		/// </summary>
		Zero = 2,
		/// <summary>
		///	Replace the value in the stencil buffer with the reference value.
		/// </summary>
		Replace = 3,
		/// <summary>
		/// Increment the value in the stencil buffer and clamp it to the maximum value.
		/// </summary>
		IncrementClamp = 4,
		/// <summary>
		/// Decrement the value in the stencil buffer and clamp it to the minimum value.
		/// </summary>
		DecrementClamp = 5,
		/// <summary>
		/// Invert the value in the stencil buffer.
		/// </summary>
		Invert = 6,
		/// <summary>
		/// Increment the value in the stencil buffer and wrap it to zero if it exceeds the maximum value.
		/// </summary>
		IncrementWrap = 7,
		/// <summary>
		/// Decrement the value in the stencil buffer and wrap it to the maximum value if it goes below zero.
		/// </summary>
		DecrementWrap = 8
	};
}