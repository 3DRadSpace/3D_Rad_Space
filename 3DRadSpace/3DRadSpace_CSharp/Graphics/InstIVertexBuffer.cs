using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIVertexBuffer : InstGPUBuffer, IVertexBuffer
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IVertexBuffer_TotalSize")]
	extern static ulong _totalSize(IntPtr vbuff);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IVertexBuffer_StructSize")]
	extern static ulong _structSize(IntPtr vbuff);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IVertexBuffer_NumVertices")]
	extern static ulong _numVerts(IntPtr vbuff);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IVertexBuffer_CreateStaging")]
	extern static IntPtr _createStaging(IntPtr vbuff);

	public InstIVertexBuffer(IntPtr handle) : base(handle)
	{
	}

	internal InstIVertexBuffer(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
	}

	public ulong TotalSize
	{
		get => _totalSize(_handle);
	}

	public ulong StructSize
	{
		get => _structSize(_handle);
	}

	public ulong NumVertices
	{
		get => _numVerts(_handle);
	}

	public IVertexBuffer CreateStaging()
	{
		return new InstIVertexBuffer(_createStaging(_handle));
	}
}
