using Engine3DRadSpace.Content;
using Engine3DRadSpace.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

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

        [DllImport("3DRadSpace.FFI.dll", EntryPoint ="E3DRSP_Game_GetMouseRay")]
        private static extern Ray _getMouseRay(
			IntPtr handle,
			Vector2 pos,
			in Matrix4x4 view, 
			in Matrix4x4 projection
		);

        public InstIGame(IntPtr handle) : base(handle, null)
		{
		}

		internal InstIGame(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
		{
		}

		public void Exit()
		{
			_exit(_handle);
		}
		
        public Ray GetMouseRay(Vector2 pos, in Matrix4x4 view, in Matrix4x4 projection)
        {
            return _getMouseRay(_handle, pos, view, projection);
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
