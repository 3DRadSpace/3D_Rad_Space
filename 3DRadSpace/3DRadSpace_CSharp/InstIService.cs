using System.Runtime.InteropServices;

namespace Engine3DRadSpace;

public abstract class InstIService : NatPtrWrapper, IService
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IService_Destroy")]
	extern static void _destroy(IntPtr handle);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IService_GetOwner")]
    extern static IntPtr _getOwner(IntPtr handle);

    protected InstIService(IntPtr handle) : base(handle, _destroy)
	{
	}

	protected InstIService(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
	{
	}

	public IGame Owner
	{
		get => new InstIGame(_getOwner(Handle), false);
	}
}
