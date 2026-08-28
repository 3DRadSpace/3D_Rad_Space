using Engine3DRadSpace.Math;
using System.Drawing;

namespace Engine3DRadSpace.Graphics;

public interface IGraphicsDevice : IPtrWrapper
{
    public string BackendName();

    public IDepthStencilState GetDepthStencilState();
    public IRasterizerState GetRasterizerState();

    public Point GetResolution();

    public IRenderTarget GetBackBuffer();
    public ITexture2D GetBackBufferTexture();
    public IDepthStencilBuffer GetDepthBuffer();

    public IBlendState CreateBlendState(
        bool alphaCoverage,
        bool indepedentBlend,
        RenderTargetBlendState[] renderTargetBlendStates
    );

    public IBlendState CreateBlendState_Opaque();
    public IBlendState CreateBlendState_AlphaBlend();
    public IBlendState CreateBlendState_Additive();
    public IBlendState CreateBlendState_NonPremultiplied();

    public IDepthStencilBuffer CreateDepthStencilBuffer(
        ulong x,
        ulong y
    );

    public IDepthStencilState CreateDepthStencilState(
        bool EnableDepth,
        DepthWriteMask Mask,
        ComparisonFunction Function,
        bool EnableStencil,
        byte ReadMask,
        byte WriteMask,
        FaceOperation FrontFace,
        FaceOperation BackFace
    );

    public IDepthStencilState CreateDepthStencilState_DepthDefault();
    public IDepthStencilState CreateDepthStencilState_DepthNone();
    public IDepthStencilState CreateDepthStencilState_DepthRead();
    public IDepthStencilState CreateDepthStencilState_DepthReverseZ();
    public IDepthStencilState CreateDepthStencilState_DepthReadReverseZ();

    public IShaderCompiler ShaderCompiler();
    /// <summary>
    /// Returns a white blank texture.
    /// </summary>
    /// <returns></returns>
    public ITexture2D WhiteBlank();

    public IVertexBuffer GetScreenQuad();

    public IIndexBuffer CreateIndexBuffer(Span<uint> indices);
    public IIndexBuffer CreateIndexBuffer(ulong numIndices, BufferUsage usage);

    public IRasterizerState CreateRasterizerState(
        RasterizerFillMode filling = RasterizerFillMode.Solid,
        RasterizerCullMode culling = RasterizerCullMode.CullBack,
        bool switchFrontBack = false,
        int depthBias = 0,
        float depthBiasClamp = 0,
        float slopeScaleDepthBias = 0,
        bool depthClip = false,
        bool scissor = false,
        bool multisample = false,
        bool aaLine = false
    );

    public IRasterizerState CreateRasterizerState_CullNone();
    public IRasterizerState CreateRasterizerState_CullClockwise();
    public IRasterizerState CreateRasterizerState_CullCounterClockwise();
    public IRasterizerState CreateRasterizerState_Wireframe();

    public IRenderTarget CreateRenderTarget(
        ulong x,
        ulong y,
        PixelFormat format
    );

    public ISamplerState CreateSamplerState();

    public ISamplerState CreateSamplerState(
        TextureFilter filter,
        TextureAddressMode addressU,
        TextureAddressMode addressV,
        TextureAddressMode addressW,
        float mipLODBias,
        uint maxAnisotropy,
        ComparisonFunction comparisonFunc,
        Math.Color borderColor,
        float minLOD,
        float maxLOD
    );

    public ISamplerState CreateSamplerState_LinearClamp();
    public ISamplerState CreateSamplerState_LinearWrap();

    public ISamplerState CreateSamplerState_PointClamp();
    public ISamplerState CreateSamplerState_PointWrap();

    public ISamplerState CreateSamplerState_AnisotropicClamp();
    public ISamplerState CreateSamplerState_AnisotropicWrap();
    public ITexture1D CreateTexture1D(ulong size, BufferUsage usage);
    public ITexture1D CreateTexture1D(Span<Math.Color> colors);

    public ITexture2D CreateTexture2D(
        IntPtr data,
        ulong x,
        ulong y,
        PixelFormat format,
        BufferUsage usage
    );

    public ITexture2D CreateTexture2D(string path);

    public ITextureCube CreateTextureCube(ITexture2D[] cubeMap);
    public ITextureCube CreateTextureCube(string path);
    public ITexture3D CreateTexture3D(ITexture3D[] textures);

    public IVertexBuffer CreateVertexBuffer(

        IntPtr data,
        ulong structSize,
        ulong numVertices,
        BufferUsage usage
    );

    public IGraphicsCommandList CreateCommandList();
    public IGraphicsCommandList ImmediateContext();

    public IntPtr NativeHandle();
}
