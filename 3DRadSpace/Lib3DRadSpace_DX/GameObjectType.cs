using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Used in I/O operations when loading.
    /// </summary>
    public enum GameObjectType : byte 
    {
        /// <summary>
        /// Represents the empty object
        /// </summary>
        Empty = 0,
        /// <summary>
        /// Represents the Camera object.
        /// </summary>
        Camera,
        /// <summary>
        /// Represents the Script object containing a C# class.
        /// </summary>
        Script,
        /// <summary>
        /// Represents the Skinmesh object
        /// </summary>
        Skinmesh,
        /// <summary>
        /// Represents a 2D imagine that is drawn into the sprite-batch.
        /// </summary>
        Sprite,
        /// <summary>
        /// Represents a text drawn into the screen.
        /// </summary>
        TextPrint,
        /// <summary>
        /// Represents a skybox.
        /// </summary>
        Skybox,

    }
}
