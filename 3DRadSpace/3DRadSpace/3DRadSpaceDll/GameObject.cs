using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Super-class defining the objects thatn can be used.
    /// </summary>
    public class GameObject
    {
        /// <summary>
        /// Object name.
        /// </summary>
        public string Name;
        /// <summary>
        /// Checks if object is enabled.
        /// </summary>
        public bool Enabled;
        /// <summary>
        /// Object position.
        /// </summary>
        public Vector3 Position;
        /// <summary>
        /// Euler angles rotation.
        /// </summary>
        public Vector3 Rotation;
        /// <summary>
        /// Scale vector
        /// </summary>
        public Vector3 Scale;
        public string Resource;
        public virtual void Load(ContentManager Content)
        {

        }
        public virtual void Draw(GameTime time,GraphicsDevice dev,SpriteBatch batch,Matrix view,Matrix projection)
        {

        }
        public virtual void EditorDraw(GameTime time, GraphicsDevice dev, SpriteBatch batch, Matrix view, Matrix projection)
        {

        }
        public virtual void Update(GameTime time,MouseState mouse,KeyboardState keyboard)
        {
            
        }
    }
}
