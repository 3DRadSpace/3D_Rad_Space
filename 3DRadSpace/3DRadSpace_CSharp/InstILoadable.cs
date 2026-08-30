using System.Runtime.InteropServices;

namespace Engine3DRadSpace;

public class InstILoadable : NatPtrWrapper, ILoadable
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ILoadable_Load2")]
	internal extern static void _load(IntPtr handle);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_ILoadable_Load2")]
	internal extern static void _load2(IntPtr handle, string path);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ILoadable_Destroy")]
	internal extern static void _destroy(IntPtr handle);

	public InstILoadable(IntPtr handle) : base(handle, null)
	{
	}

	public void Load()
	{
		_load(_handle);
	}

	public void Load(string path)
	{
		_load2(_handle, path);
	}
}
