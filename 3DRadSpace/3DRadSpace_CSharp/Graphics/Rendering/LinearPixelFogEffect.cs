using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics.Rendering
{
    public class LinearPixelFogEffect : PostProcessEffect
    {
        public LinearPixelFogEffect(IntPtr nativePtr) : base(nativePtr) { }
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_LinearPixelFogEffect_Create")]
        private static extern IntPtr E3DRSP_LinearPixelFogEffect_Create(IntPtr device);
        public LinearPixelFogEffect(IGraphicsDevice device) : base(E3DRSP_LinearPixelFogEffect_Create(device.Handle))
        {
        }
    }
}
