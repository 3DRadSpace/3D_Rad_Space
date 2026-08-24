#pragma once

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
    /// Represents all texture pixel formats supported when creating a Texture2D.
    /// Mirrors the Direct3D 11 / DXGI_FORMAT enumeration (see DXGI_FORMAT in
    /// dxgiformat.h), providing a 1:1 mapping so values can be cast/translated
    /// directly to their DXGI_FORMAT counterparts.
    /// </summary>
    enum class PixelFormat : unsigned int
    {
        /// <summary>The format is not specified. Equivalent to DXGI_FORMAT_UNKNOWN.</summary>
        Unknown = 0,
        /// <summary>A four-component, 128-bit typeless format. Equivalent to DXGI_FORMAT_R32G32B32A32_TYPELESS.</summary>
        R32G32B32A32_Typeless,
        /// <summary>A four-component, 128-bit floating-point format. Equivalent to DXGI_FORMAT_R32G32B32A32_FLOAT.</summary>
        R32G32B32A32_Float,
        /// <summary>A four-component, 128-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R32G32B32A32_UINT.</summary>
        R32G32B32A32_UnsignedInt,
        /// <summary>A four-component, 128-bit signed-integer format. Equivalent to DXGI_FORMAT_R32G32B32A32_SINT.</summary>
        R32G32B32A32_SignedInt,
        /// <summary>A three-component, 96-bit typeless format. Equivalent to DXGI_FORMAT_R32G32B32_TYPELESS.</summary>
        R32G32B32_Typeless,
        /// <summary>A three-component, 96-bit floating-point format. Equivalent to DXGI_FORMAT_R32G32B32_FLOAT.</summary>
        R32G32B32_Float,
        /// <summary>A three-component, 96-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R32G32B32_UINT.</summary>
        R32G32B32_UnsignedInt,
        /// <summary>A three-component, 96-bit signed-integer format. Equivalent to DXGI_FORMAT_R32G32B32_SINT.</summary>
        R32G32B32_SignedInt,
        /// <summary>A four-component, 64-bit typeless format. Equivalent to DXGI_FORMAT_R16G16B16A16_TYPELESS.</summary>
        R16G16B16A16_Typeless,
        /// <summary>A four-component, 64-bit floating-point format. Equivalent to DXGI_FORMAT_R16G16B16A16_FLOAT.</summary>
        R16G16B16A16_Float,
        /// <summary>A four-component, 64-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R16G16B16A16_UNORM.</summary>
        R16G16B16A16_UnsignedNormalized,
        /// <summary>A four-component, 64-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R16G16B16A16_UINT.</summary>
        R16G16B16A16_UnsignedInt,
        /// <summary>A four-component, 64-bit signed-normalized-integer format. Equivalent to DXGI_FORMAT_R16G16B16A16_SNORM.</summary>
        R16G16B16A16_SignedNormalized,
        /// <summary>A four-component, 64-bit signed-integer format. Equivalent to DXGI_FORMAT_R16G16B16A16_SINT.</summary>
        R16G16B16A16_SignedInt,
        /// <summary>A two-component, 64-bit typeless format. Equivalent to DXGI_FORMAT_R32G32_TYPELESS.</summary>
        R32G32_Typeless,
        /// <summary>A two-component, 64-bit floating-point format. Equivalent to DXGI_FORMAT_R32G32_FLOAT.</summary>
        R32G32_Float,
        /// <summary>A two-component, 64-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R32G32_UINT.</summary>
        R32G32_UnsignedInt,
        /// <summary>A two-component, 64-bit signed-integer format. Equivalent to DXGI_FORMAT_R32G32_SINT.</summary>
        R32G32_SignedInt,
        /// <summary>A two-component, 64-bit typeless format used for depth-stencil resources. Equivalent to DXGI_FORMAT_R32G8X24_TYPELESS.</summary>
        R32G8X24_Typeless,
        /// <summary>A 32-bit floating-point depth channel with an 8-bit unsigned-integer stencil channel. Equivalent to DXGI_FORMAT_D32_FLOAT_S8X24_UINT.</summary>
        D32_Float_S8X24_UnsignedInt,
        /// <summary>A 32-bit floating-point channel with 24 typeless bits. Equivalent to DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS.</summary>
        R32_Float_X8X24_Typeless,
        /// <summary>32 typeless bits with an 8-bit unsigned-integer channel and 24 typeless bits. Equivalent to DXGI_FORMAT_X32_TYPELESS_G8X24_UINT.</summary>
        X32_Typeless_G8X24_UnsignedInt,
        /// <summary>A four-component, 32-bit typeless format. Equivalent to DXGI_FORMAT_R10G10B10A2_TYPELESS.</summary>
        R10G10B10A2_Typeless,
        /// <summary>A four-component, 32-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R10G10B10A2_UNORM.</summary>
        R10G10B10A2_UnsignedNormalized,
        /// <summary>A four-component, 32-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R10G10B10A2_UINT.</summary>
        R10G10B10A2_UnsignedInt,
        /// <summary>A three-component, 32-bit floating-point format. Equivalent to DXGI_FORMAT_R11G11B10_FLOAT.</summary>
        R11G11B10_Float,
        /// <summary>A four-component, 32-bit typeless format. Equivalent to DXGI_FORMAT_R8G8B8A8_TYPELESS.</summary>
        R8G8B8A8_Typeless,
        /// <summary>A four-component, 32-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R8G8B8A8_UNORM.</summary>
        R8G8B8A8_UnsignedNormalized,
        /// <summary>A four-component, 32-bit unsigned-normalized sRGB format. Equivalent to DXGI_FORMAT_R8G8B8A8_UNORM_SRGB.</summary>
        R8G8B8A8_UnsignedNormalized_SRGB,
        /// <summary>A four-component, 32-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R8G8B8A8_UINT.</summary>
        R8G8B8A8_UnsignedInt,
        /// <summary>A four-component, 32-bit signed-normalized-integer format. Equivalent to DXGI_FORMAT_R8G8B8A8_SNORM.</summary>
        R8G8B8A8_SignedNormalized,
        /// <summary>A four-component, 32-bit signed-integer format. Equivalent to DXGI_FORMAT_R8G8B8A8_SINT.</summary>
        R8G8B8A8_SignedInt,
        /// <summary>A two-component, 32-bit typeless format. Equivalent to DXGI_FORMAT_R16G16_TYPELESS.</summary>
        R16G16_Typeless,
        /// <summary>A two-component, 32-bit floating-point format. Equivalent to DXGI_FORMAT_R16G16_FLOAT.</summary>
        R16G16_Float,
        /// <summary>A two-component, 32-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R16G16_UNORM.</summary>
        R16G16_UnsignedNormalized,
        /// <summary>A two-component, 32-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R16G16_UINT.</summary>
        R16G16_UnsignedInt,
        /// <summary>A two-component, 32-bit signed-normalized-integer format. Equivalent to DXGI_FORMAT_R16G16_SNORM.</summary>
        R16G16_SignedNormalized,
        /// <summary>A two-component, 32-bit signed-integer format. Equivalent to DXGI_FORMAT_R16G16_SINT.</summary>
        R16G16_SignedInt,
        /// <summary>A single-component, 32-bit typeless format. Equivalent to DXGI_FORMAT_R32_TYPELESS.</summary>
        R32_Typeless,
        /// <summary>A single-component, 32-bit floating-point depth format. Equivalent to DXGI_FORMAT_D32_FLOAT.</summary>
        D32_Float,
        /// <summary>A single-component, 32-bit floating-point format. Equivalent to DXGI_FORMAT_R32_FLOAT.</summary>
        R32_Float,
        /// <summary>A single-component, 32-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R32_UINT.</summary>
        R32_UnsignedInt,
        /// <summary>A single-component, 32-bit signed-integer format. Equivalent to DXGI_FORMAT_R32_SINT.</summary>
        R32_SignedInt,
        /// <summary>A 32-bit typeless format used for depth-stencil resources. Equivalent to DXGI_FORMAT_R24G8_TYPELESS.</summary>
        R24G8_Typeless,
        /// <summary>A 24-bit unsigned-normalized-integer depth channel with an 8-bit unsigned-integer stencil channel. Equivalent to DXGI_FORMAT_D24_UNORM_S8_UINT.</summary>
        D24_UnsignedNormalized_S8_UnsignedInt,
        /// <summary>A 24-bit unsigned-normalized-integer channel with 8 typeless bits. Equivalent to DXGI_FORMAT_R24_UNORM_X8_TYPELESS.</summary>
        R24_UnsignedNormalized_X8_Typeless,
        /// <summary>24 typeless bits with an 8-bit unsigned-integer channel. Equivalent to DXGI_FORMAT_X24_TYPELESS_G8_UINT.</summary>
        X24_Typeless_G8_UnsignedInt,
        /// <summary>A two-component, 16-bit typeless format. Equivalent to DXGI_FORMAT_R8G8_TYPELESS.</summary>
        R8G8_Typeless,
        /// <summary>A two-component, 16-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R8G8_UNORM.</summary>
        R8G8_UnsignedNormalized,
        /// <summary>A two-component, 16-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R8G8_UINT.</summary>
        R8G8_UnsignedInt,
        /// <summary>A two-component, 16-bit signed-normalized-integer format. Equivalent to DXGI_FORMAT_R8G8_SNORM.</summary>
        R8G8_SignedNormalized,
        /// <summary>A two-component, 16-bit signed-integer format. Equivalent to DXGI_FORMAT_R8G8_SINT.</summary>
        R8G8_SignedInt,
        /// <summary>A single-component, 16-bit typeless format. Equivalent to DXGI_FORMAT_R16_TYPELESS.</summary>
        R16_Typeless,
        /// <summary>A single-component, 16-bit floating-point format. Equivalent to DXGI_FORMAT_R16_FLOAT.</summary>
        R16_Float,
        /// <summary>A single-component, 16-bit unsigned-normalized-integer depth format. Equivalent to DXGI_FORMAT_D16_UNORM.</summary>
        D16_UnsignedNormalized,
        /// <summary>A single-component, 16-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R16_UNORM.</summary>
        R16_UnsignedNormalized,
        /// <summary>A single-component, 16-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R16_UINT.</summary>
        R16_UnsignedInt,
        /// <summary>A single-component, 16-bit signed-normalized-integer format. Equivalent to DXGI_FORMAT_R16_SNORM.</summary>
        R16_SignedNormalized,
        /// <summary>A single-component, 16-bit signed-integer format. Equivalent to DXGI_FORMAT_R16_SINT.</summary>
        R16_SignedInt,
        /// <summary>A single-component, 8-bit typeless format. Equivalent to DXGI_FORMAT_R8_TYPELESS.</summary>
        R8_Typeless,
        /// <summary>A single-component, 8-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R8_UNORM.</summary>
        R8_UnsignedNormalized,
        /// <summary>A single-component, 8-bit unsigned-integer format. Equivalent to DXGI_FORMAT_R8_UINT.</summary>
        R8_UnsignedInt,
        /// <summary>A single-component, 8-bit signed-normalized-integer format. Equivalent to DXGI_FORMAT_R8_SNORM.</summary>
        R8_SignedNormalized,
        /// <summary>A single-component, 8-bit signed-integer format. Equivalent to DXGI_FORMAT_R8_SINT.</summary>
        R8_SignedInt,
        /// <summary>A single-component, 8-bit unsigned-normalized-integer alpha-only format. Equivalent to DXGI_FORMAT_A8_UNORM.</summary>
        A8_UnsignedNormalized,
        /// <summary>A single-component, 1-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_R1_UNORM.</summary>
        R1_UnsignedNormalized,
        /// <summary>A three-component, 32-bit shared-exponent floating-point format. Equivalent to DXGI_FORMAT_R9G9B9E5_SHAREDEXP.</summary>
        R9G9B9E5_SHAREDEXP,
        /// <summary>A four-component, 32-bit unsigned-normalized-integer format used for 4:2:2 video. Equivalent to DXGI_FORMAT_R8G8_B8G8_UNORM.</summary>
        R8G8_B8G8_UnsignedNormalized,
        /// <summary>A four-component, 32-bit unsigned-normalized-integer format used for 4:2:2 video. Equivalent to DXGI_FORMAT_G8R8_G8B8_UNORM.</summary>
        G8R8_G8B8_UnsignedNormalized,
        /// <summary>A typeless block-compression format (BC1). Equivalent to DXGI_FORMAT_BC1_TYPELESS.</summary>
        BC1_Typeless,
        /// <summary>A block-compression format (BC1, formerly DXT1). Equivalent to DXGI_FORMAT_BC1_UNORM.</summary>
        BC1_UnsignedNormalized,
        /// <summary>A block-compression sRGB format (BC1). Equivalent to DXGI_FORMAT_BC1_UNORM_SRGB.</summary>
        BC1_UnsignedNormalized_SRGB,
        /// <summary>A typeless block-compression format (BC2). Equivalent to DXGI_FORMAT_BC2_TYPELESS.</summary>
        BC2_Typeless,
        /// <summary>A block-compression format (BC2, formerly DXT2/DXT3). Equivalent to DXGI_FORMAT_BC2_UNORM.</summary>
        BC2_UnsignedNormalized,
        /// <summary>A block-compression sRGB format (BC2). Equivalent to DXGI_FORMAT_BC2_UNORM_SRGB.</summary>
        BC2_UnsignedNormalized_SRGB,
        /// <summary>A typeless block-compression format (BC3). Equivalent to DXGI_FORMAT_BC3_TYPELESS.</summary>
        BC3_Typeless,
        /// <summary>A block-compression format (BC3, formerly DXT4/DXT5). Equivalent to DXGI_FORMAT_BC3_UNORM.</summary>
        BC3_UnsignedNormalized,
        /// <summary>A block-compression sRGB format (BC3). Equivalent to DXGI_FORMAT_BC3_UNORM_SRGB.</summary>
        BC3_UnsignedNormalized_SRGB,
        /// <summary>A typeless block-compression format (BC4), one component. Equivalent to DXGI_FORMAT_BC4_TYPELESS.</summary>
        BC4_Typeless,
        /// <summary>A block-compression unsigned-normalized format (BC4), one component. Equivalent to DXGI_FORMAT_BC4_UNORM.</summary>
        BC4_UnsignedNormalized,
        /// <summary>A block-compression signed-normalized format (BC4), one component. Equivalent to DXGI_FORMAT_BC4_SNORM.</summary>
        BC4_SignedNormalized,
        /// <summary>A typeless block-compression format (BC5), two components. Equivalent to DXGI_FORMAT_BC5_TYPELESS.</summary>
        BC5_Typeless,
        /// <summary>A block-compression unsigned-normalized format (BC5), two components. Equivalent to DXGI_FORMAT_BC5_UNORM.</summary>
        BC5_UnsignedNormalized,
        /// <summary>A block-compression signed-normalized format (BC5), two components. Equivalent to DXGI_FORMAT_BC5_SNORM.</summary>
        BC5_SignedNormalized,
        /// <summary>A three-component, 16-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_B5G6R5_UNORM.</summary>
        B5G6R5_UnsignedNormalized,
        /// <summary>A four-component, 16-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_B5G5R5A1_UNORM.</summary>
        B5G5R5A1_UnsignedNormalized,
        /// <summary>A four-component, 32-bit unsigned-normalized-integer format (BGRA order). Equivalent to DXGI_FORMAT_B8G8R8A8_UNORM.</summary>
        B8G8R8A8_UnsignedNormalized,
        /// <summary>A four-component, 32-bit unsigned-normalized-integer format (BGRX, alpha ignored). Equivalent to DXGI_FORMAT_B8G8R8X8_UNORM.</summary>
        B8G8R8X8_UnsignedNormalized,
        /// <summary>A four-component, 32-bit 2.8-biased fixed-point format (BGR with XR bias, alpha 2-bit). Equivalent to DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM.</summary>
        R10G10B10_XR_BIAS_A2_UnsignedNormalized,
        /// <summary>A four-component, 32-bit typeless format (BGRA order). Equivalent to DXGI_FORMAT_B8G8R8A8_TYPELESS.</summary>
        B8G8R8A8_Typeless,
        /// <summary>A four-component, 32-bit unsigned-normalized sRGB format (BGRA order). Equivalent to DXGI_FORMAT_B8G8R8A8_UNORM_SRGB.</summary>
        B8G8R8A8_UnsignedNormalized_SRGB,
        /// <summary>A four-component, 32-bit typeless format (BGRX, alpha ignored). Equivalent to DXGI_FORMAT_B8G8R8X8_TYPELESS.</summary>
        B8G8R8X8_Typeless,
        /// <summary>A four-component, 32-bit unsigned-normalized sRGB format (BGRX, alpha ignored). Equivalent to DXGI_FORMAT_B8G8R8X8_UNORM_SRGB.</summary>
        B8G8R8X8_UnsignedNormalized_SRGB,
        /// <summary>A typeless block-compression HDR format (BC6H). Equivalent to DXGI_FORMAT_BC6H_TYPELESS.</summary>
        BC6H_Typeless,
        /// <summary>An HDR block-compression format using unsigned 16-bit floats (BC6H). Equivalent to DXGI_FORMAT_BC6H_UF16.</summary>
        BC6H_UF16,
        /// <summary>An HDR block-compression format using signed 16-bit floats (BC6H). Equivalent to DXGI_FORMAT_BC6H_SF16.</summary>
        BC6H_SF16,
        /// <summary>A typeless block-compression format (BC7). Equivalent to DXGI_FORMAT_BC7_TYPELESS.</summary>
        BC7_Typeless,
        /// <summary>A block-compression unsigned-normalized format (BC7). Equivalent to DXGI_FORMAT_BC7_UNORM.</summary>
        BC7_UnsignedNormalized,
        /// <summary>A block-compression sRGB format (BC7). Equivalent to DXGI_FORMAT_BC7_UNORM_SRGB.</summary>
        BC7_UnsignedNormalized_SRGB,
        /// <summary>A four-component video resource format. Equivalent to DXGI_FORMAT_AYUV.</summary>
        AYUV,
        /// <summary>A 10-bit-per-channel packed YUV 4:4:4 video format. Equivalent to DXGI_FORMAT_Y410.</summary>
        Y410,
        /// <summary>A 16-bit-per-channel packed YUV 4:4:4 video format. Equivalent to DXGI_FORMAT_Y416.</summary>
        Y416,
        /// <summary>An 8-bit, planar 4:2:0 video resource format. Equivalent to DXGI_FORMAT_NV12.</summary>
        NV12,
        /// <summary>A 10-bit, planar 4:2:0 video resource format. Equivalent to DXGI_FORMAT_P010.</summary>
        P010,
        /// <summary>A 16-bit, planar 4:2:0 video resource format. Equivalent to DXGI_FORMAT_P016.</summary>
        P016,
        /// <summary>An 8-bit, planar 4:2:0 video format with an opaque, driver-specific layout. Equivalent to DXGI_FORMAT_420_OPAQUE.</summary>
        Video_YUV_420_Opaque,
        /// <summary>An 8-bit packed YUV 4:2:2 video resource format. Equivalent to DXGI_FORMAT_YUY2.</summary>
        YUY2,
        /// <summary>A 10-bit packed YUV 4:2:2 video resource format. Equivalent to DXGI_FORMAT_Y210.</summary>
        Y210,
        /// <summary>A 16-bit packed YUV 4:2:2 video resource format. Equivalent to DXGI_FORMAT_Y216.</summary>
        Y216,
        /// <summary>An 8-bit, planar 4:1:1 video resource format. Equivalent to DXGI_FORMAT_NV11.</summary>
        NV11,
        /// <summary>A palettized format used for palette-indexed video content. Equivalent to DXGI_FORMAT_AI44.</summary>
        AI44,
        /// <summary>A palettized format used for palette-indexed video content (swapped byte order of AI44). Equivalent to DXGI_FORMAT_IA44.</summary>
        IA44,
        /// <summary>An 8-bit palettized format. Equivalent to DXGI_FORMAT_P8.</summary>
        P8,
        /// <summary>An 8-bit palettized format with an 8-bit alpha channel. Equivalent to DXGI_FORMAT_A8P8.</summary>
        A8P8,
        /// <summary>A four-component, 16-bit unsigned-normalized-integer format. Equivalent to DXGI_FORMAT_B4G4R4A4_UNORM.</summary>
        B4G4R4A4_UnsignedNormalized,

        /// <summary>An 8-bit planar 4:2:2 video resource format. Equivalent to DXGI_FORMAT_P208.</summary>
        P208,
        /// <summary>A video resource format used for 4:2:2 chroma subsampling. Equivalent to DXGI_FORMAT_V208.</summary>
        V208,
        /// <summary>A video resource format used for 4:4:4 chroma subsampling. Equivalent to DXGI_FORMAT_V408.</summary>
        V408,
    };
}