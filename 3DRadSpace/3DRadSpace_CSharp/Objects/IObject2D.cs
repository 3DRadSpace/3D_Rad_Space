using System.Numerics;

namespace Engine3DRadSpace.Objects;

public interface IObject2D : IObject, IDrawable2D
{
	public Vector2 Position { get; set; }
	public Vector2 RotationCenter { get; set; }
	public Vector2 Scale { get; set; }
    /// <summary>
    /// Z-depth for layering 2D objects.
    /// </summary>
    public float Depth { get; set; }
	
	/// <summary>
	/// Rotation in radians.
	/// </summary>
	public float Rotation { get; set; }
}
