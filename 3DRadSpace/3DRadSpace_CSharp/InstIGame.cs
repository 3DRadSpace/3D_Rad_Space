using Engine3DRadSpace.Content;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace
{
	public class InstIGame : NatPtrWrapper, IGame
	{
		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGame_Exit")]
		private static extern void _exit(IntPtr handle);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGame_WasInitialized")]
		private static extern bool _wasInitialized(IntPtr handle);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGame_WasLoaded")]
		private static extern bool _wasLoaded(IntPtr handle);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGame_AppendScene", CharSet = CharSet.Ansi)]
		private static extern bool _appendScene(IntPtr handle, string path);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGame_Destroy")]
		private static extern void _destroy(IntPtr handle);

		public InstIGame(IntPtr handle) : base(handle, _destroy)
		{
		}

		internal InstIGame(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
		{
		}

		public void Exit()
		{
			_exit(_handle);
		}

		public bool WasInitialized
		{
			get
			{
				return _wasInitialized(_handle);
			}
		}

		public bool WasLoaded
		{
			get
			{
				return _wasLoaded(_handle);
			}
		}

		public void AppendScene(string path)
		{
			_appendScene(_handle, path);
		}
	}
}
