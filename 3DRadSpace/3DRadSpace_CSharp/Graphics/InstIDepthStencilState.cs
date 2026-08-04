using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIDepthStencilState : InstGPUResource, IDepthStencilState
{
	[DllImport("E3DRSP_IDepthStencilState_StencilRef", EntryPoint = "E3DRSP_IDepthStencilState_StencilRef")]
	static extern uint _ref(IntPtr handle);

	public InstIDepthStencilState(IntPtr handle) : base(handle) 
	{
	}

	internal InstIDepthStencilState(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
	}

	public uint StencilRef()
	{
		return _ref(_handle);
	}
}