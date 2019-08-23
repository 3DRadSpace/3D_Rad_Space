using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Camera class for 2D projects. Used to draw 2D scenes.
    /// </summary>
    public class Camera2D : GameObject
    {
        List<object> _scene;
        /// <summary>
        /// Adds an object to be drawn by the camera.
        /// </summary>
        /// <param name="obj"></param>
        public void Add(object obj)
        {
            if (obj is Sprite sp) sp.Is3D = false;
            _scene.Add(obj);
        }
        /// <summary>
        /// Camera drawing bounds.
        /// </summary>
        public Rectangle DrawingBounds;
        /// <summary>
        /// Draws the entire scene.
        /// </summary>
        /// <param name="spriteBatch">Game's sprite batch.</param>
        /// <param name="view">Not used, use the null value.</param>
        /// <param name="projection">Not used, use the null value.</param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (!Hidden)
            {
                for(int i =0; i < _scene.Count; i++)
                {
                    if (_scene[i] == null) continue;
                    if(_scene[i] is Sprite sp)
                    {
                        
                    }
                    
                }
                base.Draw(spriteBatch, view, projection);
            }
        }
    }
}
