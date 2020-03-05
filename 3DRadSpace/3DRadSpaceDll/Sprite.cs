using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;
using System.IO;
using System;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Event is invoked when the object is being clicked.
    /// </summary>
    /// <param name="sender">The clicked object</param>
    /// <param name="mouse">Mouse information.</param>
    public delegate void onClick(object sender,MouseState mouse);
    /// <summary>
    /// 2D Screen images class.
    /// </summary>
    public class Sprite : GameObject,IDisposable
    {
        /// <summary>
        /// Sprite object constructor.
        /// </summary>
        /// <param name="name">Object Name</param>
        /// <param name="active">Is this object active?</param>
        /// <param name="resource">Resource image.</param>
        /// <param name="pos">2D Position.</param>
        /// <param name="scale">Size of the sprite.</param>
        /// <param name="center_rot">Center of rotation.</param>
        /// <param name="rotation">Rotation in radians(?)</param>
        /// <param name="section">Sprite sheet section.</param>
        /// <param name="mask">Mask Color.</param>
        /// <param name="effects">Flipping effects.</param>
        /// <param name="layer">Drawing layer</param>
        public Sprite(string name,bool active,string resource,Vector2 pos,Vector2 scale,Vector2 center_rot=default,float rotation=0,Rectangle? section=default,Color mask =default,SpriteEffects effects=default,int layer=1)
        {
            Name = name;
            Enabled = active;
            Resource = resource;
            Position = pos;
            Size = scale;
            Center = center_rot;
            Rotation = rotation;
            SpriteSheetSection = section;
            Mask = mask;
            Effects = effects;
            Layer = layer;
        }
        /// <summary>
        /// Empty Sprite constructor.
        /// </summary>
        public Sprite()
        {
            Name = "Sprite";
            Enabled = false;
            Resource = null;
            Position = Vector2.Zero;
            Rotation = 0f;
            Size = Vector2.One;
            Center = Vector2.Zero;
            SpriteSheetSection = null;
            Mask = Color.White;
            Effects = SpriteEffects.None;
            Layer = 0;
        }

        /// <summary>
        /// Checks if this object is being used by a Camera2D.
        /// </summary>
        public bool IsUsedByCam2D { get; set; }
        /// <summary>
        /// Texture used to draw the sprite.
        /// </summary>
        public Texture2D Texture { get; private set; }
        /// <summary>
        /// Size of the sprite.
        /// </summary>
        public Vector2 Size
        {
            get
            {
                return size;
            }
            set
            {
                if (value.X <= 0 || value.Y <= 0) throw new System.ArgumentException("Size MUST be greater than 0.");
                else size = value;
            }
        }
        Vector2 size;
        /// <summary>
        /// Rotation of the sprite in radians.
        /// </summary>
        public new float Rotation { get; set; }
        /// <summary>
        /// Position of the sprite
        /// </summary>
        public new Vector2 Position { get; set; }
        /// <summary>
        /// Section of a sprite sheet. If not used, set this to null;
        /// </summary>
        public Rectangle? SpriteSheetSection { get; set; }
        /// <summary>
        /// Color mask.
        /// </summary>
        public Color Mask { get; set; }
        /// <summary>
        /// Center of rotation.
        /// </summary>
        public Vector2 Center { get; set; }
        /// <summary>
        /// Effects applied to the sprite.
        /// </summary>
        public SpriteEffects Effects { get; set; }
        /// <summary>
        /// Layer depth of the sprite.
        /// </summary>
        public float Layer { get; set; }
        /// <summary>
        /// Loads the texture. Notice this is not overloading the function from the GameObject class.
        /// </summary>
        /// <param name="content">Content manager.</param>
        /// <param name="gd">Graphics device. Expected to be given by the editor.</param>
        public void Load(ContentManager content,GraphicsDevice gd)
        {
            FileStream str = new FileStream(Resource, FileMode.Open);
            Texture = Texture2D.FromStream(gd, str);
            str.Close();
            str.Dispose();
            base.Load(content);
        }
        /// <summary>
        /// Draws the sprite.
        /// </summary>
        /// <param name="spriteBatch">spriteBatch used for drawing.</param>
        /// <param name="view">Use a null value.</param>
        /// <param name="projection">Use a null value.</param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            spriteBatch.Draw(Texture, Position, SpriteSheetSection, Mask, Rotation, Center, Size, Effects, Layer);
            base.Draw(spriteBatch, view, projection);
        }
        /// <summary>
        /// Drawing the sprite but for the editor.
        /// </summary>
        /// <param name="spriteBatch"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            spriteBatch.Draw(Texture, new Rectangle((int)Position.X+150, (int)Position.Y+25, (int)Size.X, (int)Size.Y), SpriteSheetSection, Mask, Rotation, Center, Effects, Layer);
            base.EditorDraw(spriteBatch, view, projection);
        }
        /// <summary>
        /// Updates the sprite (if it is clicked)
        /// </summary>
        /// <param name="mouse"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            if(Position.X >= mouse.X && mouse.X <= Position.X+Size.X &&
                Position.Y >= mouse.Y && mouse.Y <= Position.Y + Size.Y)
            {
                OnClick?.Invoke(this, mouse);
            }
            base.Update(mouse, keyboard, time);
        }
        /// <summary>
        /// Event called if the sprite is clicked
        /// </summary>
        public event onClick OnClick;
        /// <summary>
        /// Frees the loaded texture.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        bool _disposed = false;
        /// <summary>
        /// Protected Dispose().
        /// </summary>
        /// <param name="disposing"></param>
        protected void Dispose(bool disposing)
        {
            if (_disposed) return;
            if(disposing)
            {
                Texture.Dispose();
            }
            _disposed = true;
        }
    }
}
