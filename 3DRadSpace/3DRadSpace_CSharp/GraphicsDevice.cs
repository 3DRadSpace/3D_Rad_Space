using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	public class GraphicsDevice : IDisposable
	{
		private IntPtr _graphicsDeviceHandle = IntPtr.Zero;
		private bool _disposed = false;

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "??0GraphicsDevice@Engine3DRadSpace@@QEAA@PEAXII@Z")]
		static extern private IntPtr _createGraphicsDevice(IntPtr windowHandle, uint width, uint height);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "??1GraphicsDevice@Engine3DRadSpace@@QEAA@XZ")]
		static extern private void _destroyGraphicsDevice(IntPtr graphicsDeviceHandle);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?Clear@GraphicsDevice@Engine3DRadSpace@@QEAAXAEBUColor@2@@Z")]
		static extern private void _graphicsDevice_Clear(IntPtr graphicsDeviceHandle, Color clearColor);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?SetViewport@GraphicsDevice@Engine3DRadSpace@@QEAAXAEBUViewport@2@@Z")]
		static extern private void _graphicsDevice_SetViewport(IntPtr graphicsDeviceHandle, ref Viewport viewport);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?SetViewports@GraphicsDevice@Engine3DRadSpace@@QEAAXV?$span@UViewport@Engine3DRadSpace@@$0?0@std@@@Z ")]
		static extern private void _graphicsDevice_SetViewports(IntPtr graphicsDeviceHandle, IntPtr  viewports, uint numViewports);

		public GraphicsDevice(IntPtr windowHandle, uint width, uint height)
		{
			_graphicsDeviceHandle = _createGraphicsDevice(windowHandle, width, height);
		}

		public void Clear(Color clearColor)
		{
			_graphicsDevice_Clear(_graphicsDeviceHandle, clearColor);
		}

		public void SetViewport(ref Viewport viewport)
		{
			_graphicsDevice_SetViewport(_graphicsDeviceHandle, ref viewport);
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
				if(disposing)
				{

				}
				_disposed = true;
				_graphicsDeviceHandle = IntPtr.Zero;
			}
		}

		~GraphicsDevice()
		{
			Dispose(false);
		}
	}
}