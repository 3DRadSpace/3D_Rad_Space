using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIIndexBuffer : InstGPUBuffer, IIndexBuffer
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IIndexBuffer_Set")]
	extern static IntPtr _set(IntPtr buffer, uint index);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IIndexBuffer_NumIndices")]
	extern static uint _num(IntPtr buffer);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IIndexBuffer_NumIndices")]
	extern static IntPtr _staging(IntPtr buffer);

	public InstIIndexBuffer(IntPtr handle) : base(handle) 
	{
	}

	internal InstIIndexBuffer(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
	}

	public void Set(uint index)
	{
		_set(_handle, index);
	}

	public uint NumIndices()
	{
		return _num(_handle);
	}

	public IIndexBuffer CreateStaging()
	{
		return new InstIIndexBuffer(_staging(_handle));
	}
}
