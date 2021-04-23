using Microsoft.Xna.Framework;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// A object that allows forces to be applied on.
    /// </summary>
    public interface IPhysicsObject
    {
        /// <summary>
        /// Applies the specified force to the object
        /// </summary>
        /// <param name="dir"></param>
        /// <param name="intensity"></param>
        /// <param name="t"></param>
        void ApplyForce(Vector3 dir,Physics.ForceType t,float intensity);
    }
}
