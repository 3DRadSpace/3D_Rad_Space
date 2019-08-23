using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// 2D Screen images class.
    /// </summary>
    public class Sprite : GameObject
    {
        /// <summary>
        /// Checks if this object is being used by a Camera2D.
        /// </summary>
        public bool Is3D;
        /// <summary>
        /// Texture used to draw the sprite.
        /// </summary>
        public Texture2D Texture;
        /// <summary>
        /// Size of the sprite.
        /// </summary>
        public Vector2 Size;
        /// <summary>
        /// Rotation of the sprite in radians.
        /// </summary>
        public new float Rotation;
        /// <summary>
        /// Position of the sprite
        /// </summary>
        public new Vector2 Position;
    }
}
