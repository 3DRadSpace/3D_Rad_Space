using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;

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
    public class Sprite : GameObject
    {
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
                return Size;
            }
            set
            {
                if (Size.X <= 0 || Size.Y <= 0) throw new System.ArgumentException("Size MUST be greater than 0.");
                else Size = value;
            }
        }
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
        /// Loads the texture.
        /// </summary>
        /// <param name="content">Content manager.</param>
        public override void Load(ContentManager content)
        {
            Texture = content.Load<Texture2D>(Resource);
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
    }
}
