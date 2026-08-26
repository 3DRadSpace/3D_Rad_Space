using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace.Graphics.Rendering
{
    public class RenderingManager : InstIService
    {
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Create")]
        private static extern IntPtr E3DRSP_RenderingManager_Create(IntPtr device);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Add")]
        private static extern void E3DRSP_RenderingManager_Add(IntPtr manager, IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_At")]
        private static extern IntPtr E3DRSP_RenderingManager_At(IntPtr manager, UIntPtr index);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_NumPasses")]
        private static extern UIntPtr E3DRSP_RenderingManager_NumPasses(IntPtr manager);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Remove")]
        private static extern void E3DRSP_RenderingManager_Remove(IntPtr manager, UIntPtr index);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Clear")]
        private static extern void E3DRSP_RenderingManager_Clear(IntPtr manager);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Draw")]
        private static extern void E3DRSP_RenderingManager_Draw(IntPtr manager, IntPtr model, int passType);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Draw2")]
        private static extern void E3DRSP_RenderingManager_Draw2(IntPtr manager, IntPtr model, int passType);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Execute")]
        private static extern void E3DRSP_RenderingManager_Execute(IntPtr manager);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_CreateForward")]
        private static extern IntPtr E3DRSP_RenderingManager_CreateForward(IntPtr device);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_CreateTrivial")]
        private static extern IntPtr E3DRSP_RenderingManager_CreateTrivial(IntPtr device);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_CreateNull")]
        private static extern IntPtr E3DRSP_RenderingManager_CreateNull(IntPtr device);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_GetDirectionalLight")]
        private static extern DirectionalLight E3DRSP_RenderingManager_GetDirectionalLight(IntPtr manager);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_SetDirectionalLight")]
        private static extern void E3DRSP_RenderingManager_SetDirectionalLight(IntPtr manager, in DirectionalLight light);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_GetGraphicsDevice")]
        private static extern IntPtr E3DRSP_RenderingManager_GetGraphicsDevice(IntPtr manager);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_RenderingManager_Destroy")]
        private static extern void E3DRSP_RenderingManager_Destroy(IntPtr manager);

        public RenderingManager(IntPtr nativePtr) : base(nativePtr) { }

        public RenderingManager(IGraphicsDevice device) : base(E3DRSP_RenderingManager_Create(device.Handle)) { }

        public void Add(InstIRenderer renderer)
        {
            E3DRSP_RenderingManager_Add(_handle, renderer.Handle);
        }

        public IRenderer this[int index]
        {
            get
            {
                IntPtr rendererPtr = E3DRSP_RenderingManager_At(_handle, (UIntPtr)index);
                return (IRenderer)new InstIRenderer(rendererPtr);
            }
        }

        public int NumPasses => (int)E3DRSP_RenderingManager_NumPasses(_handle);

        public void Remove(int index)
        {
            E3DRSP_RenderingManager_Remove(_handle, (UIntPtr)index);
        }

        public void Clear()
        {
            E3DRSP_RenderingManager_Clear(_handle);
        }

        public void Draw(ModelMeshPart model, int passType)
        {
            E3DRSP_RenderingManager_Draw(_handle, model.Handle, passType);
        }

        public void Draw2(Model3D model, int passType)
        {
            E3DRSP_RenderingManager_Draw2(_handle, model.Handle, passType);
        }

        public void Execute()
        {
            E3DRSP_RenderingManager_Execute(_handle);
        }

        public static RenderingManager CreateForward(IGraphicsDevice device)
        {
            IntPtr ptr = E3DRSP_RenderingManager_CreateForward(device.Handle);
            return new RenderingManager(ptr);
        }

        public static RenderingManager CreateTrivial(IGraphicsDevice device)
        {
            IntPtr ptr = E3DRSP_RenderingManager_CreateTrivial(device.Handle);
            return new RenderingManager(ptr);
        }

        public static RenderingManager CreateNull(IGraphicsDevice device)
        {
            IntPtr ptr = E3DRSP_RenderingManager_CreateNull(device.Handle);
            return new RenderingManager(ptr);
        }

        public DirectionalLight DirectionalLight
        {
            get
            {
                return E3DRSP_RenderingManager_GetDirectionalLight(_handle);
            }
            set
            {
                E3DRSP_RenderingManager_SetDirectionalLight(_handle, value);
            }
        }

        public IGraphicsDevice GraphicsDevice
        {
            get
            {
                IntPtr devicePtr = E3DRSP_RenderingManager_GetGraphicsDevice(_handle);
                return new InstIGraphicsDevice(devicePtr);
            }
        }
    }
}


