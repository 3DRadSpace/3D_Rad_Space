#pragma once

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
    /// Blend state operation.
    /// </summary>
    enum class BlendOperation
    {
        /// <summary>
        /// Add source 1 and source 2.
        /// </summary>
        Add,
		/// <summary>
		/// Subtract source 1 from source 2.
		/// </summary>
        Substract,
        /// <summary>
        /// Subtract source 2 from source 1.
        /// </summary>
        ReverseSubstract,
        /// <summary>
		/// Min(source 1, source 2).
        /// </summary>
        Minimum,
        /// <summary>
		/// Max(source 1, source 2).
        /// </summary>
        Maximum,
    };
}