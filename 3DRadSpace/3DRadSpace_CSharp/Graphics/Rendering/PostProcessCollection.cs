using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics.Rendering
{
    public class PostProcessCollection : NatPtrWrapper
    {
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_CreatePostProcessCollection")]
        private static extern IntPtr E3DRSP_CreatePostProcessCollection(IntPtr device);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessCollection_Count")]
        private static extern UIntPtr E3DRSP_PostProcessCollection_Count(IntPtr collection);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessCollection_ApplyAll")]
        private static extern void E3DRSP_PostProcessCollection_ApplyAll(IntPtr collection);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessCollection_EnableAll")]
        private static extern void E3DRSP_PostProcessCollection_EnableAll(IntPtr collection);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessCollection_DisableAll")]
        private static extern void E3DRSP_PostProcessCollection_DisableAll(IntPtr collection);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_PostProcessCollection_Destroy")]
        private static extern void E3DRSP_PostProcessCollection_Destroy(IntPtr collection);

        public PostProcessCollection(IntPtr nativePtr) : base(nativePtr, null)
        {
        }

        public PostProcessCollection(IGraphicsDevice device) : base(E3DRSP_CreatePostProcessCollection(device.Handle), null)
        {
        }

        public UIntPtr Count => E3DRSP_PostProcessCollection_Count(Handle);

        public void ApplyAll()
        {
            E3DRSP_PostProcessCollection_ApplyAll(Handle);
        }

        public void EnableAll()
        {
            E3DRSP_PostProcessCollection_EnableAll(Handle);
        }

        public void DisableAll()
        {
            E3DRSP_PostProcessCollection_DisableAll(Handle);
        }
    }
}
