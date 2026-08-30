using Engine3DRadSpace.Reflection;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Content;

internal class InstIAsset : NatPtrWrapper,  IAsset
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IAsset_GetUUID")]
	static extern UUID _getUUID(IntPtr asset);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IAsset_FileExtension")]
	static extern IntPtr _fileExtension(IntPtr asset);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IAsset_Destroy")]
	static extern void _destroy(IntPtr asset);

	internal InstIAsset(IntPtr asset) : base(asset, null)
	{
	}

	public UUID UUID
	{
		get
		{
			return _getUUID(_handle);
		}
	}

	public string FileExtension
	{
		get
		{
			return Marshal.PtrToStringAnsi(_fileExtension(_handle));
		}
	}
}
