using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics.Rendering;

public class TransparentForwardRenderer : InstIRenderer
{
    public TransparentForwardRenderer(IntPtr nativePtr) : base(nativePtr) { }

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_TransparentForwardRenderer_Create")]
    private static extern IntPtr E3DRSP_TransparentForwardRenderer_Create(IntPtr device);

    public TransparentForwardRenderer(IGraphicsDevice device) : base(E3DRSP_TransparentForwardRenderer_Create(device.Handle)) 
    {
    }
}
