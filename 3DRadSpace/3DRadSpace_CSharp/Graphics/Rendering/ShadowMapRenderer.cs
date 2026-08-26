using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Numerics;

namespace Engine3DRadSpace.Graphics.Rendering
{
    public class ShadowMapRenderer : InstIRenderer
    {
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_Create")]
        private static extern IntPtr E3DRSP_ShadowMapRenderer_Create(IntPtr manager);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetShadowMapSize")]
        private static extern float E3DRSP_ShadowMapRenderer_GetShadowMapSize(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_SetShadowMapSize")]
        private static extern void E3DRSP_ShadowMapRenderer_SetShadowMapSize(IntPtr renderer, float size);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetDepthBias")]
        private static extern float E3DRSP_ShadowMapRenderer_GetDepthBias(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_SetDepthBias")]
        private static extern void E3DRSP_ShadowMapRenderer_SetDepthBias(IntPtr renderer, float depthBias);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetSlopeScaleDepthBias")]
        private static extern float E3DRSP_ShadowMapRenderer_GetSlopeScaleDepthBias(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_SetSlopeScaleDepthBias")]
        private static extern void E3DRSP_ShadowMapRenderer_SetSlopeScaleDepthBias(IntPtr renderer, float slopeScaleDepthBias);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetShadowIntensity")]
        private static extern float E3DRSP_ShadowMapRenderer_GetShadowIntensity(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_SetShadowIntensity")]
        private static extern void E3DRSP_ShadowMapRenderer_SetShadowIntensity(IntPtr renderer, float shadowIntensity);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetNearPlane")]
        private static extern float E3DRSP_ShadowMapRenderer_GetNearPlane(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_SetNearPlane")]
        private static extern void E3DRSP_ShadowMapRenderer_SetNearPlane(IntPtr renderer, float nearPlane);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetShadowMap")]
        private static extern IntPtr E3DRSP_ShadowMapRenderer_GetShadowMap(IntPtr renderer);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetSamplerState")]
        private static extern IntPtr E3DRSP_ShadowMapRenderer_GetSamplerState(IntPtr renderer);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetLightViewMatrix")]
        private static extern Matrix4x4 E3DRSP_ShadowMapRenderer_GetLightViewMatrix(IntPtr renderer, ref Vector3 lightDir);
        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ShadowMapRenderer_GetLightProjectionMatrix")]
        private static extern Matrix4x4 E3DRSP_ShadowMapRenderer_GetLightProjectionMatrix(IntPtr renderer);

        public ShadowMapRenderer(IntPtr nativePtr) : base(nativePtr)
        {
        }

        public ShadowMapRenderer(IGraphicsDevice device) : base(E3DRSP_ShadowMapRenderer_Create(device.Handle))
        {
        }

        public float ShadowMapSize
        {
            get => E3DRSP_ShadowMapRenderer_GetShadowMapSize(Handle);
            set => E3DRSP_ShadowMapRenderer_SetShadowMapSize(Handle, value);
        }

        public float DepthBias
        {
            get => E3DRSP_ShadowMapRenderer_GetDepthBias(Handle);
            set => E3DRSP_ShadowMapRenderer_SetDepthBias(Handle, value);
        }

        public float SlopeScaleDepthBias
        {
            get => E3DRSP_ShadowMapRenderer_GetSlopeScaleDepthBias(Handle);
            set => E3DRSP_ShadowMapRenderer_SetSlopeScaleDepthBias(Handle, value);
        }

        public float ShadowIntensity
        {
            get => E3DRSP_ShadowMapRenderer_GetShadowIntensity(Handle);
            set => E3DRSP_ShadowMapRenderer_SetShadowIntensity(Handle, value);
        }

        public float NearPlane
        {
            get => E3DRSP_ShadowMapRenderer_GetNearPlane(Handle);
            set => E3DRSP_ShadowMapRenderer_SetNearPlane(Handle, value);
        }

        public IDepthStencilBuffer ShadowMap => new InstIDepthStencilBuffer(E3DRSP_ShadowMapRenderer_GetShadowMap(Handle));
        public ISamplerState SamplerState => new InstISamplerState(E3DRSP_ShadowMapRenderer_GetSamplerState(Handle));

        public Matrix4x4 GetLightViewMatrix(Vector3 lightDir)
        {
            return E3DRSP_ShadowMapRenderer_GetLightViewMatrix(Handle, ref lightDir);
        }

        public Matrix4x4 GetLightProjectionMatrix()
        {
            return E3DRSP_ShadowMapRenderer_GetLightProjectionMatrix(Handle);
        }
    }
}
