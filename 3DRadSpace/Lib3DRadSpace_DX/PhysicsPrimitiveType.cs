namespace Lib3DRadSpace_DX.Physics
{
    /// <summary>
    /// 
    /// </summary>
    public enum PhysicsPrimitiveType : byte
    {
        /// <summary>
        /// Defines nothing. Represents 0 floats.
        /// </summary>
        Nonexistent,
        /// <summary>
        /// Represents a box. Uses 6 (3x2) floats.
        /// </summary>
        Box,
        /// <summary>
        /// Represents a sphere. Uses 4 floats
        /// </summary>
        Sphere,
    }
}
