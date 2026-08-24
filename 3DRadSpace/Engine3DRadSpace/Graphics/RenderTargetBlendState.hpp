#pragma once
#include "Blend.hpp"
#include "BlendOperation.hpp"
#include "ColorWriteEnable.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the blend state for a render target.
	/// </summary>
    struct RenderTargetBlendState
    {
        /// <summary>
        /// Indicates whether blending is enabled for the render target.
        /// </summary>
        bool EnableBlending;
		/// <summary>
		/// The source blend factor for color blending.
		/// </summary>
        Blend SourceBlend;
		/// <summary>
		/// The destination blend factor for color blending.
		/// </summary>
        Blend DestinationBlend;
		/// <summary>
		/// The blend operation for color blending.
		/// </summary>
        BlendOperation BlendOp;
		/// <summary>
		/// The source blend factor for alpha blending.
		/// </summary>
        Blend SourceBlendAlpha;
		/// <summary>
		/// The destination blend factor for alpha blending.
		/// </summary>
        Blend DestinationBlendAlpha;
		/// <summary>
		/// The blend operation for alpha blending.
		/// </summary>
        BlendOperation BlendOpAlpha;
		/// <summary>
		/// The color write mask for the render target.
		/// </summary>
        ColorWriteEnable WriteMask;
    };
}