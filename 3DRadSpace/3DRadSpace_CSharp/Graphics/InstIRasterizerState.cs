namespace Engine3DRadSpace.Graphics;

public class InstIRasterizerState : InstGPUResource, IRasterizerState
{
	public InstIRasterizerState(IntPtr handle) : base(handle) 
	{
	}

	internal InstIRasterizerState(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
	}
}
