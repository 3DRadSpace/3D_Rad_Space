using Microsoft.Xna.Framework;
using System;

namespace Lib3DRadSpace_DX.Physics
{
    /// <summary>
    /// 
    /// </summary>
    public struct PhysicsPrimitive
    {
        /// <summary>
        /// 
        /// </summary>
        public PhysicsPrimitiveType Type;
        /// <summary>
        /// 
        /// </summary>
        public float[] Coordinates;
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sph"></param>
        public PhysicsPrimitive(BoundingSphere sph)
        {
            Type = PhysicsPrimitiveType.Sphere;
            Coordinates = new float[4];
            Coordinates[0] = sph.Center.X;
            Coordinates[1] = sph.Center.Y;
            Coordinates[2] = sph.Center.Z;
            Coordinates[3] = sph.Radius;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="box"></param>
        public PhysicsPrimitive(BoundingBox box)
        {
            Type = PhysicsPrimitiveType.Box;
            Coordinates = new float[6];
            Coordinates[0] = box.Min.X;
            Coordinates[1] = box.Min.Y;
            Coordinates[2] = box.Min.Z;
            Coordinates[3] = box.Max.X - box.Min.X;
            Coordinates[4] = box.Max.Y - box.Min.Y;
            Coordinates[5] = box.Max.Z - box.Min.Z;
        }
    }
}
