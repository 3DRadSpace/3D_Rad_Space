#pragma once

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
    /// Specifies blend factors, which modulate values for the pixel shader and render target.
    /// Mimics the DirectX11 <c>D3D11_BLEND</c> enumeration.
    /// </summary>
    enum class Blend
    {
        /// <summary>The blend factor is (0, 0, 0, 0). No pre-blend operation.</summary>
        Zero = 0,

        /// <summary>The blend factor is (1, 1, 1, 1). No pre-blend operation.</summary>
        One,

        /// <summary>The blend factor is (Rs, Gs, Bs, As), the pixel shader output color.</summary>
        SourceColor,

        /// <summary>The blend factor is (1 - Rs, 1 - Gs, 1 - Bs, 1 - As), the inverse of the pixel shader output color.</summary>
        InverseSourceColor,

        /// <summary>The blend factor is (As, As, As, As), the alpha component of the pixel shader output color.</summary>
        SourceAlpha,

        /// <summary>The blend factor is (1 - As, 1 - As, 1 - As, 1 - As), the inverse of the alpha component of the pixel shader output color.</summary>
        InverseSourceAlpha,

        /// <summary>The blend factor is (Ad, Ad, Ad, Ad), the alpha component of the render target.</summary>
        DestinationAlpha,

        /// <summary>The blend factor is (1 - Ad, 1 - Ad, 1 - Ad, 1 - Ad), the inverse of the alpha component of the render target.</summary>
        InverseDestinationAlpha,

        /// <summary>The blend factor is (Rd, Gd, Bd, Ad), the color of the render target.</summary>
        DestinationColor,

        /// <summary>The blend factor is (1 - Rd, 1 - Gd, 1 - Bd, 1 - Ad), the inverse of the color of the render target.</summary>
        InverseDestinationColor,

        /// <summary>The blend factor is (f, f, f, 1), where f = min(As, 1 - Ad). Clamps the alpha value of the source color.</summary>
        SourceAlphaSat,

        /// <summary>The blend factor is the constant blend factor set with the pipeline's blend state.</summary>
        BlendFactor,

        /// <summary>The blend factor is the inverse of the constant blend factor set with the pipeline's blend state.</summary>
        InverseBlendFactor,

        /// <summary>The blend factor is (Rs1, Gs1, Bs1, As1), the second pixel shader output color (dual-source blending).</summary>
        Source1Color,

        /// <summary>The blend factor is (1 - Rs1, 1 - Gs1, 1 - Bs1, 1 - As1), the inverse of the second pixel shader output color (dual-source blending).</summary>
        Source1InverseColor,

        /// <summary>The blend factor is (As1, As1, As1, As1), the alpha component of the second pixel shader output color (dual-source blending).</summary>
        Source1Alpha,

        /// <summary>The blend factor is (1 - As1, 1 - As1, 1 - As1, 1 - As1), the inverse of the alpha component of the second pixel shader output color (dual-source blending).</summary>
        InverseSource1Alpha
    };
}