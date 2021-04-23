using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FontStashSharp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Represents a drawable 2D text.
    /// </summary>
    public class TextPrint : BaseGameObject
    {
        FontSystem _font;
        SpriteFontBase _sfont;
        int _fontsize;
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name">Name of the object</param>
        /// <param name="visible">Checks if the font is visible</param>
        /// <param name="fontpath">Path to a Font file</param>
        /// <param name="text">Rendered text</param>
        /// <param name="fsize">Font size in pixels</param>
        /// <param name="pos">Position in screen space coordinates</param>
        /// <param name="rotation">The rotation in radians</param>
        /// <param name="rotationcenter">Represents the rotation center</param>
        /// <param name="scale">Represents the text scale</param>
        /// <param name="col">Represents the text color</param>
        public TextPrint(string name="TextPrint",bool visible=true, string fontpath="",string text="Hello world!",int fsize=15,Vector2 pos=default,float rotation=0,Vector2 rotationcenter=default,Vector2? scale = null,Color? col=null)
        {
            Name = name;
            Visible = visible;
            Asset = fontpath;
            Text = text;
            Position = pos;
            Rotation = rotation;
            RotationCenter = rotationcenter;
            Scale = scale ?? Vector2.One;
            _fontsize = fsize;
            Colour = col ?? Color.White;
            _font = FontSystemFactory.Create(CurrentProject.GraphicsDevice);
        }
        /// <summary>
        /// Represents the TextPrint position in the screen-space coordinates.
        /// </summary>
        public new Vector2 Position;

        /// <summary>
        /// Represents the rotation in radians.
        /// </summary>
        public new float Rotation;

        /// <summary>
        /// Represents the rotation center offset.
        /// </summary>
        public new Vector2 RotationCenter;

        /// <summary>
        /// Represents the text scaling.
        /// </summary>
        public new Vector2 Scale;

        /// <summary>
        /// Represents the text used.
        /// </summary>
        public string Text;

        /// <summary>
        /// Represents the text color.
        /// </summary>
        public Color Colour;

        /// <summary>
        /// Loads the font used for drawing the string.
        /// </summary>
        /// <param name="content">Not used here.</param>
        public override void Load(ContentManager content)
        {
            _font.AddFont(File.ReadAllBytes(Asset));
            _sfont = _font.GetFont(_fontsize);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="time"></param>
        /// <param name="batch"></param>
        public override void Draw2D(GameTime time, SpriteBatch batch)
        {
            batch.DrawString(_sfont, Text, Position, Colour,Scale,Rotation,RotationCenter);
        }
        /// <summary>
        /// Gets the string lenght and width in pixels. No scalling applied.
        /// </summary>
        /// <returns></returns>
        public Vector2 GetLenghtPx()
        {
            return _sfont.MeasureString(Text);
        }
        /// <summary>
        /// Unloads the font.
        /// </summary>
        public override void Unload()
        {
            _font.Dispose();
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        /// <param name="position"></param>
        /// <param name="result"></param>
        public override void LoadF(byte[] buff, ref int position, out IGameObject result)
        {
            string name = ByteCodeParser.GetString(buff, ref position);
            bool visible = ByteCodeParser.GetBool(buff, ref position);
            string fontpath = ByteCodeParser.GetString(buff, ref position);
            string text = ByteCodeParser.GetString(buff, ref position);
            int fsize = ByteCodeParser.GetInt(buff, ref position);
            Vector2 pos = ByteCodeParser.GetVector2(buff, ref position);
            Vector3 rot = ByteCodeParser.GetVector3(buff, ref position);
            Vector2 scal = ByteCodeParser.GetVector2(buff, ref position);
            Color colour = ByteCodeParser.GetColor(buff, ref position);
            result = new TextPrint(name,visible,fontpath,text,fsize,pos,rot.X,new Vector2(rot.Y,rot.Z),scal,colour);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        public override void SaveF(List<byte> buff)
        {
            ByteCodeParser.SetString(buff, Name);
            ByteCodeParser.SetBool(buff, Visible);
            ByteCodeParser.SetString(buff, Asset);
            ByteCodeParser.SetString(buff, Text);
            ByteCodeParser.SetInt(buff, _fontsize);
            ByteCodeParser.SetVector2(buff, Position);
            ByteCodeParser.SetVector3(buff, new Vector3(Rotation,RotationCenter.X,RotationCenter.Y));
            ByteCodeParser.SetVector2(buff, Scale);
            ByteCodeParser.SetColor(buff, Colour);
        }
    }
}
