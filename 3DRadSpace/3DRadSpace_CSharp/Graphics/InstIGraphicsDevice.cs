using System.Drawing;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIGraphicsDevice : InstIService, IGraphicsDevice
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_Destroy")]
	extern static void _destroy(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IGraphicsDevice_BackendName")]
	extern static string _backendName(IntPtr handle);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_GetDepthStencilState")]
    extern static IntPtr _getdepthStencilState(IntPtr handle);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_GetRasterizerState")]
	extern static IntPtr _getRasterizerState(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_Resolution")]
	extern static Internal.Point _resolution(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_GetBackBuffer")]
	extern static IntPtr _getbackBuffer(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_GetDepthBuffer")]
	extern static IntPtr _getDepthBuffer(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateBlendState")]
	extern static IntPtr _createBlendState(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateBlendState")]
	extern static IntPtr _createBlendState(
		IntPtr handle,
		byte bAlphaCoverage, 
		byte bIndepedentBlend, 
		RenderTargetBlendState renderTargetBlendState1,
		RenderTargetBlendState renderTargetBlendState2,
		RenderTargetBlendState renderTargetBlendState3,
		RenderTargetBlendState renderTargetBlendState4,
		RenderTargetBlendState renderTargetBlendState5,
		RenderTargetBlendState renderTargetBlendState6,
		RenderTargetBlendState renderTargetBlendState7,
		RenderTargetBlendState renderTargetBlendState8
	);


	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateBlendState_Opaque")]
	extern static IntPtr _createBlendStateOpaque(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateBlendState_AlphaBlend")]
	extern static IntPtr _createBlendStateAlphaBlend(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateBlendState_Additive")]
	extern static IntPtr _createBlendStateAdditive(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateBlendState_NonPremultiplied")]
	extern static IntPtr _createBlendStateNonPremultiplied(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateDepthStencilBuffer")]
	extern static IntPtr _createDepthStencilBuffer(IntPtr handle, ulong x, ulong y);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateDepthStencilState")]
	extern static IntPtr _createDepthStencilState(
		IntPtr handle,
		byte enableDepth,
		DepthWriteMask mask,
		ComparisonFunction function,
		byte enableStencil,
		byte readMask,
		byte writeMask,
		FaceOperation frontFace,
		FaceOperation backFace
	);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthDefault")]
	extern static IntPtr _createDepthStencilState_depthDefault(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthNone")]
	extern static IntPtr _createDepthStencilState_depthNone(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthRead")]
	extern static IntPtr _createDepthStencilState_depthRead(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthReverseZ")]
	extern static IntPtr _createDepthStencilState_depthReverseZ(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthReadReverseZ")]
	extern static IntPtr _createDepthStencilState_depthReadReverseZ(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_ShaderCompiler")]
	extern static IntPtr _shaderCompiler(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_WhiteBlank")]
	extern static IntPtr _whiteTexture(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_GetScreenQuad")]
	extern static IntPtr _screenQuad(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateIndexBuffer")]
	extern static IntPtr _createIndexBuffer(IntPtr handle, IntPtr indices, ulong numIndices);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateIndexBuffer2")]
	extern static IntPtr _createIndexBuffer2(IntPtr handle, ulong numIndices, BufferUsage bufferUsage);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateRasterizerState")]
	extern static IntPtr _createRasterizerState(
		IntPtr handle,
		RasterizerFillMode filling,
		RasterizerCullMode culling,
		byte switchFrontBack,
		int depthBias,
		float depthBiasClamp,
		float slopeScaleDepthBias,
		byte depthClip,
		byte scissor,
		byte multisample,
		byte aaLine
	);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateRasterizerState_CullNone")]
	extern static IntPtr _createRasterizerState_cullNone(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateRasterizerState_CullClockwise")]
	extern static IntPtr _createRasterizerState_cullCW(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateRasterizerState_CullCounterClockwise")]
	extern static IntPtr _createRasterizerState_cullCCW(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateRasterizerState_Wireframe")]
	extern static IntPtr _createRasterizerState_wireframe(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateRenderTarget")]
	extern static IntPtr _createRT(
		IntPtr handle,
		ulong x,
		ulong y,
		PixelFormat format
	);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState")]
	extern static IntPtr _createSamplerState(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState2")]
	extern static IntPtr _createSamplerState2(
		IntPtr handle,
		TextureFilter filter,
		TextureAddressMode addressU,
		TextureAddressMode addressV,
		TextureAddressMode addressW,
		float mipLODBias,
		uint maxAnisotropy,
		ComparisonFunction comparisonFunc,
		IntPtr borderColor,
		float minLOD,
		float maxLOD
	);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState_LinearClamp")]
	extern static IntPtr _createSamplerState_LinearClamp(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState_LinearWrap")]
	extern static IntPtr _createSamplerState_LinearWrap(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState_PointClamp")]
	extern static IntPtr _createSamplerState_PointClamp(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState_PointWrap")]
	extern static IntPtr _createSamplerState_PointWrap(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState_AnisotropicClamp")]
	extern static IntPtr _createSamplerState_AnisotropicClamp(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateSamplerState_AnisotropicWrap")]
	extern static IntPtr _createSamplerState_AnisotropicWrap(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateTexture1D")]
	extern static IntPtr _createTexture1D(IntPtr handle, ulong size, BufferUsage usage);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateTexture1DCol")]
	unsafe extern static IntPtr _createTexture1D(IntPtr handle, Math.Color *colors, ulong numColors);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateTexture2D")]
	extern static IntPtr _createTexture2D(
		IntPtr handle,
		IntPtr data,
		ulong x,
		ulong y,
		PixelFormat format,
		BufferUsage usage
	);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IGraphicsDevice_CreateTexture2DFromFile")]
	extern static IntPtr _createTexture2D(IntPtr handle, string path);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IGraphicsDevice_CreateTextureCube")]
	extern static unsafe IntPtr _createTextureCube(IntPtr handle, IntPtr* textureCubeArray);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IGraphicsDevice_CreateTextureCubeFromFile")]
	extern static IntPtr _createTextureCube(IntPtr handle, string path);

    [DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IGraphicsDevice_CreateTexture3D")]
    extern static unsafe IntPtr _createTexture3D(IntPtr handle, IntPtr* ppTextures, ulong numTextures);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateVertexBuffer")]
	extern static IntPtr _createVertexBuffer(
		IntPtr handle,
		IntPtr data,
		ulong structSize,
		ulong numVertices,
		BufferUsage usage
	);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_CreateCommandList")]
	extern static IntPtr _createCommandList(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_ImmediateContext")]
	extern static IntPtr _immediateContext(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsDevice_NativeHandle")]
	extern static IntPtr _nativeHandle(IntPtr handle);

	public InstIGraphicsDevice(IntPtr handle) : base(handle, _destroy)
	{
	}

	internal InstIGraphicsDevice(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
	{
	}

	public string BackendName()
	{
		return _backendName(_handle);
	}

	public IBlendState CreateBlendState(bool alphaCoverage, bool indepedentBlend, RenderTargetBlendState[] renderTargetBlendStates)
	{
		return new InstIBlendState(_createBlendState(
			_handle,
			alphaCoverage ? (byte)1 : (byte)0,
			indepedentBlend ? (byte)1 : (byte)0,
			renderTargetBlendStates[0],
			renderTargetBlendStates[1],
			renderTargetBlendStates[2],
			renderTargetBlendStates[3],
			renderTargetBlendStates[4],
			renderTargetBlendStates[5],
			renderTargetBlendStates[6],
			renderTargetBlendStates[7]
			)
		);
	}

	public IBlendState CreateBlendState_Additive()
	{
		return new InstIBlendState(_createBlendStateAdditive(_handle));
	}

	public IBlendState CreateBlendState_AlphaBlend()
	{
		return new InstIBlendState(_createBlendStateAlphaBlend(_handle));
	}

	public IBlendState CreateBlendState_NonPremultiplied()
	{
		return new InstIBlendState(_createBlendStateNonPremultiplied(_handle));
	}

	public IBlendState CreateBlendState_Opaque()
	{
		return new InstIBlendState(_createBlendStateOpaque(_handle));
	}

	public IGraphicsCommandList CreateCommandList()
	{
		return new InstIGraphicsCommandList(_createCommandList(_handle));
	}

	public IDepthStencilBuffer CreateDepthStencilBuffer(ulong x, ulong y)
	{
		return new InstIDepthStencilBuffer(_createDepthStencilBuffer(_handle, x, y));
	}

	public IDepthStencilState CreateDepthStencilState(bool EnableDepth, DepthWriteMask Mask, ComparisonFunction Function, bool EnableStencil, byte ReadMask, byte WriteMask, FaceOperation FrontFace, FaceOperation BackFace)
	{
		return new InstIDepthStencilState(_createDepthStencilState(
			_handle,
			EnableDepth ? (byte)1 : (byte)0,
			Mask,
			Function,
			EnableStencil ? (byte)1 : (byte)0,
			ReadMask,
			WriteMask,
			FrontFace,
			BackFace
			)
		);
	}

	public IDepthStencilState CreateDepthStencilState_DepthDefault()
	{
		return new InstIDepthStencilState(_createDepthStencilState_depthDefault(_handle));
	}

	public IDepthStencilState CreateDepthStencilState_DepthNone()
	{
		return new InstIDepthStencilState(_createDepthStencilState_depthNone(_handle));
	}

	public IDepthStencilState CreateDepthStencilState_DepthRead()
	{
		return new InstIDepthStencilState(_createDepthStencilState_depthRead(_handle));
	}

	public IDepthStencilState CreateDepthStencilState_DepthReadReverseZ()
	{
		return new InstIDepthStencilState(_createDepthStencilState_depthReadReverseZ(_handle));
	}

	public IDepthStencilState CreateDepthStencilState_DepthReverseZ()
	{
		return new InstIDepthStencilState(_createDepthStencilState_depthReverseZ(_handle));
	}

	public unsafe IIndexBuffer CreateIndexBuffer(Span<uint> indices)
	{
		fixed (uint* pIndices = indices)
		{
			return new InstIIndexBuffer(_createIndexBuffer(_handle, (IntPtr)pIndices, (ulong)indices.Length));
		}
	}

	public IIndexBuffer CreateIndexBuffer(ulong numIndices, BufferUsage usage)
	{
		return new InstIIndexBuffer(_createIndexBuffer2(_handle, numIndices, usage));
	}

	public IRasterizerState CreateRasterizerState(RasterizerFillMode filling = RasterizerFillMode.Solid, RasterizerCullMode culling = RasterizerCullMode.CullBack, bool switchFrontBack = false, int depthBias = 0, float depthBiasClamp = 0, float slopeScaleDepthBias = 0, bool depthClip = false, bool scissor = false, bool multisample = false, bool aaLine = false)
	{
		return new InstIRasterizerState(_createRasterizerState(
			_handle,
			filling,
			culling,
			switchFrontBack ? (byte)1 : (byte)0,
			depthBias,
			depthBiasClamp,
			slopeScaleDepthBias,
			depthClip ? (byte)1 : (byte)0,
			scissor ? (byte)1 : (byte)0,
			multisample ? (byte)1 : (byte)0,
			aaLine ? (byte)1 : (byte)0
		));
	}

	public IRasterizerState CreateRasterizerState_CullClockwise()
	{
		return new InstIRasterizerState(_createRasterizerState_cullCW(_handle));
	}

	public IRasterizerState CreateRasterizerState_CullCounterClockwise()
	{
		return new InstIRasterizerState(_createRasterizerState_cullCCW(_handle));
	}

	public IRasterizerState CreateRasterizerState_CullNone()
	{
		return new InstIRasterizerState(_createRasterizerState_cullNone(_handle));
	}

	public IRasterizerState CreateRasterizerState_Wireframe()
	{
		return new InstIRasterizerState(_createRasterizerState_wireframe(_handle));
	}

	public IRenderTarget CreateRenderTarget(ulong x, ulong y, PixelFormat format)
	{
		return new InstIRenderTarget(_createRT(_handle, x, y, format));
	}

	public ISamplerState CreateSamplerState()
	{
		return new InstISamplerState(_createSamplerState(_handle));
	}

	unsafe public ISamplerState CreateSamplerState(TextureFilter filter, TextureAddressMode addressU, TextureAddressMode addressV, TextureAddressMode addressW, float mipLODBias, uint maxAnisotropy, ComparisonFunction comparisonFunc, Math.Color borderColor, float minLOD, float maxLOD)
	{
		return new InstISamplerState(_createSamplerState2(
			_handle,
			filter,
			addressU,
			addressV,
			addressW,
			mipLODBias,
			maxAnisotropy,
			comparisonFunc,
			(IntPtr)(&borderColor),
			minLOD,
			maxLOD
		));
	}

	public ISamplerState CreateSamplerState_AnisotropicClamp()
	{
		return new InstISamplerState(_createSamplerState_AnisotropicClamp(_handle));
	}

	public ISamplerState CreateSamplerState_AnisotropicWrap()
	{
		return new InstISamplerState(_createSamplerState_AnisotropicWrap(_handle));
	}

	public ISamplerState CreateSamplerState_LinearClamp()
	{
		return new InstISamplerState(_createSamplerState_LinearClamp(_handle));
	}

	public ISamplerState CreateSamplerState_LinearWrap()
	{
		return new InstISamplerState(_createSamplerState_LinearWrap(_handle));
	}

	public ISamplerState CreateSamplerState_PointClamp()
	{
		return new InstISamplerState(_createSamplerState_PointClamp(_handle));
	}

	public ISamplerState CreateSamplerState_PointWrap()
	{
		return new InstISamplerState(_createSamplerState_PointWrap(_handle));
	}

	public ITexture1D CreateTexture1D(ulong size, BufferUsage usage)
	{
		return new InstITexture1D(_createTexture1D(_handle, size, usage));
	}

	public unsafe ITexture1D CreateTexture1D(Span<Math.Color> colors)
	{
		fixed (Math.Color* pColors = colors)
		{
			return new InstITexture1D(_createTexture1D(_handle, pColors, (ulong)colors.Length));
		}
	}

	public ITexture2D CreateTexture2D(nint data, ulong x, ulong y, PixelFormat format, BufferUsage usage)
	{
		return new InstITexture2D(_createTexture2D(_handle, data, x, y, format, usage));
	}

	public ITexture2D CreateTexture2D(string path)
	{
		return new InstITexture2D(_createTexture2D(_handle, path));
	}

	public unsafe ITextureCube CreateTextureCube(ITexture2D[] cubeMap)
	{
		IntPtr* pTextures = stackalloc IntPtr[6];
		for (int i = 0; i < 6; i++)
		{
			pTextures[i] = cubeMap[i].Handle;
		}

		return new InstITextureCube(_createTextureCube(_handle, pTextures));
	}

	public unsafe ITexture3D CreateTexture3D(ITexture3D[] textures)
	{
		int numTextures = textures.Length;

		IntPtr* pTextures = stackalloc IntPtr[numTextures];
		for(int i =0; i < numTextures; i++)
		{
			pTextures[i] = textures[i].Handle;
		}

		return new InstITexture3D(_createTexture3D(_handle, pTextures, (ulong)numTextures));
	}

	public ITextureCube CreateTextureCube(string path)
	{
		return new InstITextureCube(_createTextureCube(_handle, path));
    }

    public IVertexBuffer CreateVertexBuffer(nint data, ulong structSize, ulong numVertices, BufferUsage usage)
	{
		return new InstIVertexBuffer(_createVertexBuffer(_handle, data, structSize, numVertices, usage));
	}

	public IRenderTarget GetBackBuffer()
	{
		return new InstIRenderTarget(_getbackBuffer(_handle), ownsHandle: false);
	}

	public ITexture2D GetBackBufferTexture()
	{
		return new InstITexture2D(_getbackBuffer(_handle), ownsHandle: false);
	}

	public IDepthStencilBuffer GetDepthBuffer()
	{
		return new InstIDepthStencilBuffer(_getDepthBuffer(_handle), ownsHandle: false);
	}

	public IDepthStencilState GetDepthStencilState()
	{
		return new InstIDepthStencilState(_getdepthStencilState(_handle), ownsHandle: false);
	}

	public IRasterizerState GetRasterizerState()
	{
		return new InstIRasterizerState(_getRasterizerState(_handle), ownsHandle: false);
	}

	public Point GetResolution()
	{
		var p = _resolution(_handle);
		return new Point(p.X, p.Y);
	}

	public IVertexBuffer GetScreenQuad()
	{
		return new InstIVertexBuffer(_screenQuad(_handle));
	}

	public IGraphicsCommandList ImmediateContext()
	{
		return new InstIGraphicsCommandList(_immediateContext(_handle));
	}

	public nint NativeHandle()
	{
		return _nativeHandle(_handle);
	}

	public IShaderCompiler ShaderCompiler()
	{
		return new InstIShaderCompiler(_shaderCompiler(_handle));
	}

	public ITexture2D WhiteBlank()
	{
		return new InstITexture2D(_whiteTexture(_handle));
	}
}
