using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIRenderTarget : NatPtrWrapper, IRenderTarget
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IRenderTarget_Destroy")]
	extern static void _destroy(IntPtr rt);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IRenderTarget_RenderTargetHandle")]
	extern static IntPtr _rt(IntPtr rt);

	public InstIRenderTarget(IntPtr handle) : base(handle, _destroy)
	{
	}

	internal InstIRenderTarget(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
	{
	}

	public IntPtr RenderTargetHandle
	{
		get
		{
			return _rt(_handle);
		}
	}
}
