using System.Runtime.InteropServices;
using Engine3DRadSpace.Native;
using Engine3DRadSpace.Graphics;

namespace Engine3DRadSpace;

public class Game : InstIGame
{
	protected List<Tuple<int, object>> objects;

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Game_Create")]
	static extern private IntPtr _createGame(string title, ulong width, ulong height);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Game_Run")]
	static extern private void _runGame(IntPtr gameHandle);

    [DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Game_RunOneFrame")]
    static extern private void _runOneFrame(IntPtr gameHandle);

    public Game(string title, uint width = 800, uint height = 600) : base(_createGame(title, (ulong)width, (ulong)height))
	{
		
	}
	public void Run()
	{
		_runGame(_handle);
	}

	public void RunOneFrame()
	{
		_runOneFrame(_handle);
	}
}
