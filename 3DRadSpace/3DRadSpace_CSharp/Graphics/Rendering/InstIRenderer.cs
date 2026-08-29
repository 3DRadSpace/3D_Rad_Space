using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics.Rendering
{
    public class InstIRenderer : NatPtrWrapper
    {
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IRenderer_Begin")]
        private static extern void E3DRSP_IRenderer_Begin(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IRenderer_Draw")]
        private static extern void E3DRSP_IRenderer_Draw(IntPtr renderer, in MeshPartDrawInfo descriptor);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IRenderer_End")]
        private static extern void E3DRSP_IRenderer_End(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IRenderer_IsRenderPassTypeSupported")]
        private static extern bool E3DRSP_IRenderer_IsRenderPassTypeSupported(IntPtr renderer, int passType);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IRenderer_Destroy")]
        private static extern void E3DRSP_IRenderer_Destroy(IntPtr renderer);

        public InstIRenderer(IntPtr nativePtr) : base(nativePtr, null) { }

        public void Begin() => E3DRSP_IRenderer_Begin(_handle);
        public void Draw(MeshPartDrawInfo meshPart) => E3DRSP_IRenderer_Draw(_handle, in meshPart);
        public void End() => E3DRSP_IRenderer_End(_handle);
        public bool IsRenderPassTypeSupported(int passType) => E3DRSP_IRenderer_IsRenderPassTypeSupported(_handle, passType); 
    }
}
