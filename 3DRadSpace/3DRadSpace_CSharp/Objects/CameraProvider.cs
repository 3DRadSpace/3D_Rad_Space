using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace.Objects
{
    public class CameraProvider : NatPtrWrapper
    {
        [DllImport("3DRadSpace.FFI.dll")]
        static extern private IntPtr E3DRSP_CameraProvider_Create(IntPtr owner);

        [DllImport("3DRadSpace.FFI.dll")]
        static extern private IntPtr E3DRSP_CameraProvider_At(IntPtr provider, ulong index);

        [DllImport("3DRadSpace.FFI.dll")]
        static extern private IntPtr E3DRSP_CameraProvider_GetActiveCamera(IntPtr provider);

        [DllImport("3DRadSpace.FFI.dll")]
        static extern private void E3DRSP_CameraProvider_SetActiveCamera(IntPtr provider, IntPtr camera);

        [DllImport("3DRadSpace.FFI.dll")]
        static extern private void E3DRSP_CameraProvider_SetActiveCamera2(IntPtr provider, ulong indexCamera);

        [DllImport("3DRadSpace.FFI.dll")]
        static extern private void E3DRSP_CameraProvider_Refresh(IntPtr provider);

        [DllImport("3DRadSpace.FFI.dll")]
        static extern private ulong E3DRSP_CameraProvider_Count(IntPtr provider);

        public CameraProvider(IntPtr natPtr) : base(natPtr, null)
        {
        }

        public CameraProvider(IGame owner) : base(E3DRSP_CameraProvider_Create((owner as NatPtrWrapper).Handle), null)
        {
        }

        public ICamera this[ulong index]
        {
            get
            {
                var ptr = E3DRSP_CameraProvider_At(_handle, index);
                return new InstICamera(ptr);
            }
        }

        public ICamera GetActiveCamera()
        {
            return new InstICamera(E3DRSP_CameraProvider_GetActiveCamera(_handle));
        }

        public void SetActiveCamera(ICamera camera)
        {
            E3DRSP_CameraProvider_SetActiveCamera(_handle, (camera as NatPtrWrapper).Handle);
        }

        public void SetActiveCamera(ulong indexCamera)
        {
            E3DRSP_CameraProvider_SetActiveCamera2(_handle, indexCamera);
        }

        public void Refresh()
        {
            E3DRSP_CameraProvider_Refresh(_handle);
        }

        public ulong Count
        {
            get => E3DRSP_CameraProvider_Count(_handle);
        }
    }
}
