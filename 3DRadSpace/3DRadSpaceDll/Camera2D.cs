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
        /// Camera2D constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="enabled">Is the camera drawing the scene?</param>
        /// <param name="Pos">Position</param>
        /// <param name="Size">Size</param>
        public Camera2D(string name, bool enabled, Vector2 Pos, Vector2 Size)
        {
            Name = name;
            Enabled = enabled;
            DrawingBounds = new Rectangle((int)Pos.X,(int) Pos.Y,(int) Size.X,(int) Size.Y);
            _scene = new List<object>();
        }
        /// <summary>
        /// Adds an object to be drawn by the camera.
        /// </summary>
        /// <param name="obj">Object to be added.</param>
        public void Add(object obj)
        {
            if (obj is Sprite sp) sp.IsUsedByCam2D = true;
            _scene.Add(obj);
        }
        /// <summary>
        /// Camera drawing bounds.
        /// </summary>
        public Rectangle DrawingBounds { get; set; }
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
                        if (sp.IsUsedByCam2D)
                        {
                            if (DrawingBounds.X >= sp.Position.X && DrawingBounds.X + DrawingBounds.Width >= sp.Position.X + sp.Size.X &&
                            DrawingBounds.Y >= sp.Position.Y && DrawingBounds.Y + DrawingBounds.Height >= sp.Position.Y + sp.Size.Y)
                            {
                                spriteBatch.Draw(sp.Texture, new Rectangle((int)sp.Position.X, (int)sp.Position.Y, (int)(sp.Position.X + sp.Size.X), (int)(sp.Position.Y + sp.Size.Y)), sp.SpriteSheetSection, sp.Mask, sp.Rotation, sp.Center, sp.Effects, sp.Layer); ;
                            }
                        }
                    }
                    
                }
                base.Draw(spriteBatch, view, projection);
            }
        }
    }
}
