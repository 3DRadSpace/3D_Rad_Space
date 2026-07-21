using Microsoft.Xna.Framework;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Represents a 3D object capable of rendering a scene.
    /// </summary>
    public interface IRenderer
    {
        /// <summary>
        /// Gets the view matrix.
        /// </summary>
        Matrix View { get; }
        /// <summary>
        /// Gets the projection matrix.
        /// </summary>
        Matrix Projection { get; }
        /// <summary>
        /// Gets the camera frustrum.
        /// </summary>
        BoundingFrustum CameraFrustum { get; }

        /// <summary>
        /// Defines the minimum draw distance.
        /// </summary>
        float NearPlaneDistance { get; set; }

        /// <summary>
        /// Defines the maximum draw distance.
        /// </summary>
        float FarPlaneDistance { get; set; }

        ///<summary>
        ///Determines the position of the camera in the world space.
        ///</summary>
        Vector3 Position { get; }
    }
}
