using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Class for drawing 2D Texts.
    /// </summary>
    public class TextPrint : GameObject,IDisposable
    {
        /// <summary>
        /// TextPrint constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="active">Will this object draw?</param>
        /// <param name="text">Text to print</param>
        /// <param name="pos">Position on the screen</param>
        /// <param name="size">Size</param>
        /// <param name="rotation">Rotation in radians(?)</param>
        /// <param name="font">Font used for drawing.</param>
        /// <param name="cof">Center of rotation.</param>
        /// <param name="col">Text color.</param>
        /// <param name="effects">Flipping options.</param>
        /// <param name="layer">Depth layer.</param>
        public TextPrint(string name,bool active,string font,string text,Vector2 pos,Vector2 size,float rotation=0,Vector2 cof=default,Color col=default,SpriteEffects effects=SpriteEffects.None,int layer=0)
        {
            Name = name;
            Enabled = active;
            Resource = font;
            Text = text;
            Position = pos;
            Size = size;
            Rotation = rotation;
            Center = cof;
            Color = col;
            Effects = effects;
            Layer = layer;
        }
        /// <summary>
        /// Text to be drawn
        /// </summary>
        public string Text
        {
            get
            {
                return _text;
            }
            set
            {
                if (string.IsNullOrEmpty(value) == false) _text = value;
                else throw new ArgumentNullException("Text", "Text cannot be null or empty.");
            }
        }

        string _text;

        /// <summary>
        /// Position in 2D space of the text.
        /// </summary>
        public new Vector2 Position { get; set; }

        /// <summary>
        /// Size of the text.
        /// </summary>
        public Vector2 Size
        {
            get
            {
                return _size;
            }
            set
            {
                if (value.X < 0 || value.Y < 0) throw new ArgumentOutOfRangeException("Size", value, "Size must be non-negative");
                else _size = value;
            }
        }
        Vector2 _size;
        /// <summary>
        /// Text rotation.
        /// </summary>
        public new float Rotation { get; set; }

        /// <summary>
        /// Font used for drawing the text.
        /// </summary>
        public SpriteFont Font { get; set; }

        /// <summary>
        /// Text Color.
        /// </summary>
        public Color Color { get; set; }

        /// <summary>
        /// Center of rotation.
        /// </summary>
        public Vector2 Center { get; set; }
        
        /// <summary>
        /// Allows flipping
        /// </summary>
        public SpriteEffects Effects { get; set; }

        /// <summary>
        /// Depth layer.
        /// </summary>
        public int Layer { get; set; }

        /// <summary>
        /// Loads the font.
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            Font = content.Load<SpriteFont>(Resource);
            base.Load(content);
        }

        /// <summary>
        /// Draws the text to the game screen.
        /// </summary>
        /// <param name="spriteBatch">SpriteBatch used for drawing the text.</param>
        /// <param name="view">Not used.</param>
        /// <param name="projection">Not used.</param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            spriteBatch.DrawString(Font, Text, Position, Color, Rotation, Center, Size, Effects, Layer);
            base.Draw(spriteBatch, view, projection);
        }
        /// <summary>
        /// Draws the text for the editor.
        /// </summary>
        /// <param name="spriteBatch"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            spriteBatch.DrawString(Font, Text, Position+new Vector2(150,25), Color, Rotation, Center, Size, Effects, Layer);
            base.EditorDraw(spriteBatch, view, projection);
        }

        /// <summary>
        /// Disposes the font's texture
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        bool disposed;
        /// <summary>
        /// Not really needed, MG's pipeline takes care of the SpriteFont instance.
        /// </summary>
        /// <param name="disposing"></param>
        protected virtual void Dispose(bool disposing)
        {
            if (disposed) return;
            if(disposing)
            {
                //Font.Texture.Dispose(); <-- temporarly disabled since it's possible that the Content is manaing the SpriteFont instance itself.
            }
            disposed = true;
        }
    }
}
