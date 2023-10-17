using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	public class Window
	{
		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "??0Window@Engine3DRadSpace@@QEAA@PEBDHH@Z")]
		private static extern IntPtr window_Create(string title, uint width, uint height);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?NativeHandle@Window@Engine3DRadSpace@@QEAAPEAXXZ")]
		private static extern IntPtr window_NativeHandle(IntPtr window);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?ProcessMessages@Window@Engine3DRadSpace@@QEAAXXZ")]
		private static extern void window_ProcessMessages(IntPtr window);

		private IntPtr windowHandle;

		public Window(string title, uint width, uint height)
		{
			windowHandle = window_Create(title, width, height);
		}

		public IntPtr NativeHandle
		{
			get
			{
				return window_NativeHandle(windowHandle);
			}
		}

		public void ProcessMessages()
		{
			window_ProcessMessages(windowHandle);
		}
	}
}
