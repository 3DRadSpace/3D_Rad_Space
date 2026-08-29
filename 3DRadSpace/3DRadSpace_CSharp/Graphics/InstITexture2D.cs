using Engine3DRadSpace.Reflection;
using System.Drawing;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstITexture2D : InstGPUMultiBuffer, ITexture2D
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ITexture2D_Size")]
	extern static Internal.Point _size(IntPtr texture);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ITexture2D_Width")]
	extern static uint _w(IntPtr texture);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ITexture2D_Height")]
	extern static uint _h(IntPtr texture);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ITexture2D_GetViewHandle")]
	extern static IntPtr _viewHandle(IntPtr texture);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ITexture2D_CreateStaging")]
	extern static IntPtr _createStaging(IntPtr texture);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_ITexture2D_SaveToFile")]
	extern static IntPtr _save(IntPtr texture, string path);

	public InstITexture2D(IntPtr handle) : base(handle)
	{
	}

	internal InstITexture2D(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
	}

	public Point Size
	{
		get
		{
			var s = _size(_handle);
			return new Point(s.X, s.Y);
		}
	}

	public uint Width
	{
		get => _w(_handle);
	}

	public uint Height
	{
		get => _h(_handle);
	}

	public IntPtr ViewHandle
	{
		get => _viewHandle(_handle);
	}

	public ITexture2D CreateStaging()
	{
		return new InstITexture2D(_createStaging(_handle));
	}

	public void SaveToFile(string path)
	{
		_save(_handle, path);
	}

	public static UUID UUID
	{
		get
		{
			return new UUID(0x5aae5c7a, 0xc0e7, 0x405a, 0xb6, 0xfd, 0x3, 0xcf, 0x9e, 0x3e, 0x36, 0xcc);
		}
	}
}
