using System.Runtime.InteropServices;
using Engine3DRadSpace.Native;
using Engine3DRadSpace.Graphics;
using Engine3DRadSpace.Graphics.Rendering;
using Engine3DRadSpace.Physics;
using Engine3DRadSpace.Objects;
using Engine3DRadSpace.Content;
using Engine3DRadSpace.Input;

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

	[DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetSpriteBatch(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetIGraphicsDevice(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetPostProcessCollection(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetIPhysicsEngine(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetRenderingManager(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetObjectList(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetContentManager(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetCameraProvider(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private Mouse E3DRSP_Game_GetMouse(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private IntPtr E3DRSP_Game_GetKeyboard(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private float E3DRSP_Game_GetDrawDeltaTime(IntPtr game);

    [DllImport("3DRadSpace.FFI.dll")]
    static extern private float E3DRSP_Game_GetUpdateDeltaTime(IntPtr game);

    public Game(string title, uint width = 800, uint height = 600) : base(_createGame(title, (ulong)width, (ulong)height))
	{
		
	}

    public Game(IntPtr handle) : base(handle)
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

	public SpriteBatch SpriteBatch
	{
		get => new SpriteBatch(E3DRSP_Game_GetSpriteBatch(_handle));
    }

	public IGraphicsDevice GraphicsDevice
    {
        get => new InstIGraphicsDevice(E3DRSP_Game_GetIGraphicsDevice(_handle));
    }

	public PostProcessCollection PostProcessCollection
    {
        get => new PostProcessCollection(E3DRSP_Game_GetPostProcessCollection(_handle));
    }

	public IPhysicsEngine PhysicsEngine
    {
        get => new IPhysicsEngine(E3DRSP_Game_GetIPhysicsEngine(_handle));
    }

    public RenderingManager RenderingManager
    {
        get => new RenderingManager(E3DRSP_Game_GetRenderingManager(_handle));
    }

    public ObjectList ObjectList
    {
        get => new ObjectList(E3DRSP_Game_GetObjectList(_handle));
    }

    public ContentManager ContentManager
    {
        get => new ContentManager(E3DRSP_Game_GetContentManager(_handle));
    }

    public CameraProvider CameraProvider
    {
        get => new CameraProvider(E3DRSP_Game_GetCameraProvider(_handle));
    }

    public Mouse Mouse
    {
        get => E3DRSP_Game_GetMouse(_handle);
    }

    public Keyboard Keyboard
    {
        get => new Keyboard(E3DRSP_Game_GetKeyboard(_handle));
    }

    public float DrawDeltaTime
    {
        get => E3DRSP_Game_GetDrawDeltaTime(_handle);
    }

    public float UpdateDeltaTime
    {
        get => E3DRSP_Game_GetUpdateDeltaTime(_handle);
    }
}
