using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics.Rendering
{
    public class PostProcessEffect : InstIShader
    {
        public PostProcessEffect(IntPtr nativePtr) : base(nativePtr) 
        {
        }

        public PostProcessEffect(IGraphicsDevice device, ShaderDesc desc) : base(E3DRSP_PostProcessEffect_Create(device.Handle, desc.Handle))
        {
        }

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessEffect_Create")]
        private static extern IntPtr E3DRSP_PostProcessEffect_Create(IntPtr device, IntPtr desc);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessEffect_GetEnabled")]
        private static extern bool E3DRSP_PostProcessEffect_GetEnabled(IntPtr effect);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessEffect_SetEnabled")]
        private static extern void E3DRSP_PostProcessEffect_SetEnabled(IntPtr effect, bool enabled);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessEffect_GetNotDepthAware")]
        private static extern bool E3DRSP_PostProcessEffect_GetNotDepthAware(IntPtr effect);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessEffect_SetNotDepthAware")]
        private static extern void E3DRSP_PostProcessEffect_SetNotDepthAware(IntPtr effect, bool notDepthAware);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessEffect_Draw")]
        private static extern void E3DRSP_PostProcessEffect_Draw(IntPtr effect);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessEffect_Destroy")]
        private static extern void E3DRSP_PostProcessEffect_Destroy(IntPtr effect);

        public bool Enabled
        {
            get => E3DRSP_PostProcessEffect_GetEnabled(Handle);
            set => E3DRSP_PostProcessEffect_SetEnabled(Handle, value);
        }

        public bool NotDepthAware
        {
            get => E3DRSP_PostProcessEffect_GetNotDepthAware(Handle);
            set => E3DRSP_PostProcessEffect_SetNotDepthAware(Handle, value);
        }

        public void Draw()
        {
            E3DRSP_PostProcessEffect_Draw(Handle);
        }
    }
}
