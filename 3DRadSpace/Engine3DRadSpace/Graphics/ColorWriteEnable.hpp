#pragma once

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
	/// Enables writing to the specified color channels in a render target.
    /// </summary>
    enum class ColorWriteEnable
    {
        /// <summary>
        /// Enables writing to the red(R) channel only.
        /// </summary>
        Red = 1,
		/// <summary>
		/// Enables writing to the green(G) channel only.
		/// </summary>
        Green = 2,
        /// <summary>
		/// Enables writing to the blue(B) channel only.
        /// </summary>
        Blue = 4,
		/// <summary>
		/// Enables writing to the alpha(A) channel only.
		/// </summary>
        Alpha = 8,
        /// <summary>
		/// Enables writing to all color channels (R, G, B, A).
        /// </summary>
		All = Red | Green | Blue | Alpha
    };
}