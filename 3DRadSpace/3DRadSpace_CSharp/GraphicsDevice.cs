using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	public class GraphicsDevice : IDisposable
	{
		private IntPtr _graphicsDeviceHandle = IntPtr.Zero;
		private bool _disposed = false;

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.ThisCall, EntryPoint = "??0GraphicsDevice@Engine3DRadSpace@@QEAA@PEAXII@Z")]
		static extern private IntPtr _createGraphicsDevice(IntPtr windowHandle, uint width, uint height);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.ThisCall, EntryPoint = "??1GraphicsDevice@Engine3DRadSpace@@QEAA@XZ")]
		static extern private void _destroyGraphicsDevice(IntPtr graphicsDeviceHandle);
		
		public GraphicsDevice(IntPtr windowHandle, uint width, uint height)
		{
			_graphicsDeviceHandle = _createGraphicsDevice(windowHandle, width, height);
		}

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		private void Dispose(bool disposing)
		{
			if(!_disposed)
			{
				_destroyGraphicsDevice(_graphicsDeviceHandle);
				_disposed = true;
				_graphicsDeviceHandle = IntPtr.Zero;
			}
		}
	}
}