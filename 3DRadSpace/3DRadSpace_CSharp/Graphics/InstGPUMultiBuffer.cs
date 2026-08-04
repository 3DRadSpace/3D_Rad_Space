using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics
{
	public class InstGPUMultiBuffer : InstGPUResource, IGPUMultiBuffer
	{
		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUMultiBuffer_ReadData")]
		extern static ulong _readData(IntPtr res, ulong subresource, IntPtr ppData);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUMultiBuffer_SetData")]
		extern static void _writeData(IntPtr res, ulong subresource, IntPtr pData, ulong dataSize);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGPUMultiBuffer_EndRead")]
		extern static void _endRead(IntPtr res, ulong subresource);

		public InstGPUMultiBuffer(IntPtr handle) : base(handle)
		{
		}

		protected InstGPUMultiBuffer(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
		{
		}

		public void EndRead(ulong subresource)
		{
			_endRead(_handle, subresource);
		}

		public ulong ReadData(ulong subresource, nint ppData)
		{
			return _readData(_handle, subresource, ppData);
		}

		public void SetData(ulong subresource, nint pData, ulong buffSize)
		{
			_writeData(_handle, subresource, pData, buffSize);
		}
	}
}
