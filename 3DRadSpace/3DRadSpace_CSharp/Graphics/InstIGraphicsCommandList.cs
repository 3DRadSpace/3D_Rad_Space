using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

class InstIGraphicsCommandList : InstGPUResource, IGraphicsCommandList
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_Clear")]
	extern static void _clear(IntPtr resource, IntPtr color);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_ClearRenderTarget")]
	extern static void _clearRT(IntPtr resource, IntPtr rt, IntPtr color);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_ClearDepthBuffer")]
	extern static void _clearDB(IntPtr resource, IntPtr db);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetViewport")]
	extern static void _setViewportDefault(IntPtr resource);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetViewport2")]
	extern static void _setViewport(IntPtr resource, IntPtr pViewport);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetViewports")]
	extern static void _setViewports(IntPtr resource, IntPtr ppViewports, ulong numViewports);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetViewports")]
	extern static Viewport _getViewport(IntPtr resource);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetRenderTarget")]
	extern static void _setRenderTarget(IntPtr resource, IntPtr rt);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_UnbindDepthBuffer")]
	extern static void _unbindDepth(IntPtr resource);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "SE3DRSP_IGraphicsCommandList_SetRenderTargetAndDepth")]
	extern static void _setRTandDepth(IntPtr resource, IntPtr rt, IntPtr depth);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetRenderTargetAndDisableDepth")]
	extern static void _setRTnoDepth(IntPtr resource, IntPtr rt);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_DrawVertexBuffer")]
	extern static void _draw(IntPtr resource, IntPtr vbuff, uint start);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_DrawVertexBufferWithindices")]
	extern static void _drawIndexed(IntPtr resource, IntPtr vbuff, IntPtr ibuff);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_DrawVertexBufferWithindices2")]
	extern static void _drawIndexed2(IntPtr resource, IntPtr vbuff, IntPtr ibuff, uint numIndices);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetShader")]
	extern static void _setShader(IntPtr resource, IntPtr shader);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetRasterizerState")]
	extern static void _setRS(IntPtr resource, IntPtr rs);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetDepthStencilBuffer")]
	extern static void _setDSB(IntPtr resource, IntPtr depthStencilBuff);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetDepthStencilState")]
	extern static void _setDSS(IntPtr resource, IntPtr depthState, uint sample);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetBlendState")]
	extern static void _setBlend(IntPtr resource, IntPtr blend, IntPtr blendFactor, uint sampleMask);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetTopology")]
	extern static void _setTopology(IntPtr resource, VertexTopology topology);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_DrawAuto")]
	extern static void _drawAuto(IntPtr resource);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_Present")]
	extern static void _present(IntPtr resource);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IGraphicsCommandList_SaveBackBufferToFile")]
	extern static void _saveBackBuffer(IntPtr resource, string path);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_ResizeBackBuffer")]
	extern static void _resizeBackBuffer(IntPtr resource, IntPtr pPoint);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_SetFullScreen")]
	extern static void _setFullScreen(IntPtr resource, byte fullscreen);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_Copy")]
	extern static void _copy(IntPtr resource, IntPtr dest, IntPtr src);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGraphicsCommandList_UnbindRenderTargetAndDepth")]
	extern static void _unbindRTD(IntPtr resource);

	public InstIGraphicsCommandList(IntPtr handle) : base(handle, false) 
	{
	}

	public unsafe void Clear(Color clearColor)
	{
		_clear(_handle, (nint)(&clearColor));
	}

	public void ClearDepthBuffer(IDepthStencilBuffer depth)
	{
		_clearDB(_handle, depth.Handle);
	}

	unsafe void _clearRenderTarget(IntPtr pRT, Color color)
	{
		_clearRT(_handle, pRT, (nint)(&color));
	}

	public void ClearRenderTarget(IRenderTarget rt, Color color)
	{
		_clearRenderTarget(rt.Handle, color);
	}

	public void Copy(IGPUBuffer dest, IGPUBuffer src)
	{
		_copy(_handle, dest.Handle, src.Handle);
	}

	public void DrawAuto()
	{
		_drawAuto(_handle);
	}

	public void DrawVertexBuffer(IVertexBuffer vertexBuffer, uint startSlot = 0)
	{
		_draw(_handle, vertexBuffer.Handle, startSlot);
	}

	public void DrawVertexBufferWithindices(IVertexBuffer vertexBuffer, IIndexBuffer indexBuffer)
	{
		_drawIndexed(_handle, vertexBuffer.Handle, indexBuffer.Handle);
	}

	public void DrawVertexBufferWithindices(IVertexBuffer vertexBuffer, IIndexBuffer indexBuffer, uint numIndices)
	{
		_drawIndexed2(_handle, vertexBuffer.Handle, indexBuffer.Handle, numIndices);
	}

	public Viewport GetViewport()
	{
		return _getViewport(_handle);
	}

	public void Present()
	{
		_present(_handle);
	}

	public unsafe void ResizeBackBuffer(System.Drawing.Point newResolution)
	{
		Internal.Point p = new Internal.Point(newResolution.X, newResolution.Y);
		_resizeBackBuffer(_handle, (IntPtr)(&p));
	}

	public void SaveBackBufferToFile(string path)
	{
		_saveBackBuffer(_handle, path);
	}

	public unsafe void SetBlendState(IBlendState blendState, Math.Color blendFactor, uint sampleMask = uint.MaxValue)
	{
		_setBlend(_handle, blendState.Handle, (IntPtr)(&blendFactor), sampleMask);
	}

	public void SetDepthStencilBuffer(IDepthStencilBuffer depthBuffer)
	{
		_setDSB(_handle, depthBuffer.Handle);
	}

	public void SetDepthStencilState(IDepthStencilState depthState, uint reference)
	{
		_setDSS(_handle, depthState.Handle, reference);
	}

	public void SetRasterizerState(IRasterizerState state)
	{
		_setRS(_handle, state.Handle);
	}

	public void SetRenderTarget(IRenderTarget renderTarget)
	{
		_setRenderTarget(_handle, renderTarget.Handle);
	}

	public void SetRenderTargetAndDepth(IRenderTarget renderTarget, IDepthStencilBuffer depthBuffer)
	{
		_setRTandDepth(_handle, renderTarget.Handle, depthBuffer.Handle);
	}

	public void SetRenderTargetAndDisableDepth(IRenderTarget renderTarget)
	{
		_setRTnoDepth(_handle, renderTarget.Handle);
	}

	public void SetShader(IShader shader)
	{
		_setShader(_handle, shader.Handle);
	}

	public void SetTopology(VertexTopology topology)
	{
		_setTopology(_handle, topology);
	}

	public void SetViewport()
	{
		_setViewportDefault(_handle);
	}

	public unsafe void SetViewport(Viewport viewport)
	{
		_setViewport(_handle, (IntPtr)(&viewport));
	}

	public unsafe void SetViewports(Span<Viewport> viewports)
	{  
		fixed(Viewport* pViewports = viewports)
		{
			_setViewports(_handle, (IntPtr)pViewports, (ulong)viewports.Length);
		}
	}

	public void SetFullScreen(bool fullscreen)
	{
		_setFullScreen(_handle, fullscreen ? (byte)1 : (byte)0);
	}

	public void UnbindDepthBuffer()
	{
		_unbindDepth(_handle);
	}

	public void UnbindRenderTargetAndDepth()
	{
		_unbindRTD(_handle);
	}
}
