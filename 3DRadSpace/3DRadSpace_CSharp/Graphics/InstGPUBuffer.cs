using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstGPUBuffer : InstGPUResource, IGPUBuffer
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUBuffer_ReadData")]
	extern static ulong _read(IntPtr res, IntPtr ppData);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUBuffer_SetData")]
	extern static void _write(IntPtr res, IntPtr pData, ulong buffSize);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUBuffer_EndRead")]
	extern static void _end(IntPtr res);

	public InstGPUBuffer(IntPtr handle) : base(handle)
	{
	}

	protected InstGPUBuffer(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
	}

	public void EndRead()
	{
		_end(_handle);
	}

	public ulong ReadData(nint ppData)
	{
		return _read(_handle, ppData);
	}

	public void SetData(nint pData, ulong buffSize)
	{
		_write(_handle, pData, buffSize);
	}
}
