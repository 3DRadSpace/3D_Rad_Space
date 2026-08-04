using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstGPUResource : NatPtrWrapper, IGPUResource
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUResource_GetGraphicsDevice")]
	extern static IntPtr _device(IntPtr resource);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUResource_GetHandle")]
	extern static IntPtr _natHandle(IntPtr resource);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUResource_Destroy")]
	extern static void _destroy(IntPtr resource);

	protected InstGPUResource(IntPtr handle) : base(handle, _destroy)
	{
	}

	protected InstGPUResource(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
	{
	}

	public IGraphicsDevice GraphicsDevice => new InstIGraphicsDevice(_device(_handle), ownsHandle: false);

	public IntPtr GPUHandle => _natHandle(_handle);
}
