using System.Runtime.InteropServices;

namespace Engine3DRadSpace;

public abstract class InstIUpdateable : NatPtrWrapper, IUpdateable
{
    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IUpdateable_Update")]
    extern static void _update(IntPtr handle);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IUpdateable_Destroy")]
    extern static void _destroy(IntPtr handle);

    internal InstIUpdateable(IntPtr handle) : base(handle, _destroy)
    {
    }

    protected InstIUpdateable(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
    {
    }

    public void Update()
    {
        _update(_handle);
    }
}
