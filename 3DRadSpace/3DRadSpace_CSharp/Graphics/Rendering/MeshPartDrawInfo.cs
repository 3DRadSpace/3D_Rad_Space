using Engine3DRadSpace.Graphics;
using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Graphics.Rendering
{
    public struct MeshPartDrawInfo
    {
        public IntPtr Part;
        public RenderPassType PassType;
        public System.Numerics.Matrix4x4 World;
        public System.Numerics.Matrix4x4 View;
        public System.Numerics.Matrix4x4 Projection;

        public MeshPartDrawInfo(IntPtr part, RenderPassType passType, System.Numerics.Matrix4x4 world, System.Numerics.Matrix4x4 view, System.Numerics.Matrix4x4 projection)
        {
            Part = part;
            PassType = passType;
            World = world;
            View = view;
            Projection = projection;
        }

        public MeshPartDrawInfo(ModelMeshPart part, RenderPassType passType, System.Numerics.Matrix4x4 world, System.Numerics.Matrix4x4 view, System.Numerics.Matrix4x4 projection)
        {
            Part = part.Handle;
            PassType = passType;
            World = world;
            View = view;
            Projection = projection;
        }
    }
}
