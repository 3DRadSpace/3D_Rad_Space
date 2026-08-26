using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics.Rendering;

public class ForwardRenderer : InstIRenderer
{
    public ForwardRenderer(IntPtr nativePtr) : base(nativePtr) { }

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ForwardRenderer_Create")]
    private static extern IntPtr E3DRSP_ForwardRenderer_Create(IntPtr device);

    public ForwardRenderer(IGraphicsDevice device) : base(E3DRSP_ForwardRenderer_Create(device.Handle)) 
    {
    }
}
