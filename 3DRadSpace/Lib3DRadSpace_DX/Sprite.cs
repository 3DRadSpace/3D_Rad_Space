using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;
using System.IO;
using System.Collections.Generic;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Represents a image that can be drawn into the screen.
    /// Supports these formats: BMP, GIF, JPG, PNG, TIFF, DSS (simple textures). May support other formats, but will nor support TGA.
    /// </summary>
    public class Sprite : BaseGameObject
    {
        /// <summary>
        /// Main Sprite constructor.
        /// </summary>
        /// <param name="name">Name tag of the object.</param>
        /// <param name="visible">Checks if the object is visible.</param>
        /// <param name="asset">Asset path.</param>
        /// <param name="pos">Screen space position coordinate. Default is 0,0.</param>
        /// <param name="rot">Rotation in radians. Default is 0,0.</param>
        /// <param name="center">Center of rotation. Default is 0,0 .</param>
        /// <param name="scale">Size of the sprite in screen space coordinates. Default is sx=0.1,sy=0.1</param>
        /// <param name="mask">Color mask. Default is R=255,G=255,B=255,A=255</param>
        public Sprite(string name="Sprite",bool visible=true,string asset="",Vector2 pos=default,float rot=0,Vector2 center=default,Vector2? scale=null,Color? mask=null)
        {
            Name = name;
            Visible = visible;
            Asset = asset;
            Position = pos;
            Rotation = rot;
            RotationCenter = center;
            Scale = scale ?? new Vector2(0.1f,0.1f);
            Mask = mask ?? Color.White;
        }
        /// <summary>
        /// Represents the position in a [0,0] -> [1,1] coordonate system
        /// </summary>
        public new Vector2 Position;

        /// <summary>
        /// Represents the sprite's rotation in radians.
        /// </summary>
        public new float Rotation;

        /// <summary>
        /// Represents the sprite's rotation center offset.
        /// </summary>
        public new Vector2 RotationCenter;

        /// <summary>
        /// Represents the Sprite's size in a [0,0]->[1,1] coordinate system.
        /// </summary>
        public new Vector2 Scale;

        /// <summary>
        /// Represents the ID3D11Texture2D used by the sprite.
        /// </summary>
        public Texture2D Texture;

        /// <summary>
        /// Represents the mask color used when drawing.
        /// </summary>
        public Color Mask;

        /// <summary>
        /// Represents the rectangle containing the position and scale translations given to the sprite image.
        /// </summary>
        public Rectangle DrawingRectangle
        {
            get
            {
                float sx = CurrentProject.Resolution.X;
                float sy = CurrentProject.Resolution.Y;
                return new Rectangle((int)(Position.X * sx), (int)(Position.Y * sy), (int)(Scale.X * sx), (int)(Scale.Y * sy));
            }
        }

        /// <summary>
        /// Loads the sprite image.
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            FileStream fstr = new FileStream(Asset, FileMode.Open);
            Texture = Texture2D.FromStream(CurrentProject.GraphicsDevice, fstr);
            fstr.Dispose();
        }

        /// <summary>
        /// Draws the sprite in the 2D stage.
        /// </summary>
        /// <param name="time">Not used</param>
        /// <param name="batch">Used for drawing the sprite.</param>
        public override void Draw2D(GameTime time, SpriteBatch batch)
        {
            batch.Draw(Texture, DrawingRectangle, null, Mask, Rotation, RotationCenter, SpriteEffects.None, 0f);
        }

        /// <summary>
        /// Checks if mouse is over the sprite.
        /// </summary>
        /// <param name="mouse">MouseInput.</param>
        /// <returns>Returns true if mouse is over the sprite image, or false if otherwise.</returns>
        public bool Hovered(MouseState mouse)
        {
            return DrawingRectangle.Contains(mouse.Position);
        }
        /// <summary>
        /// Checks if the sprite image is right-clicked.
        /// </summary>
        /// <param name="mouse">Mouse input struct</param>
        /// <returns></returns>
        public bool RightClicked(MouseState mouse)
        {
            return (DrawingRectangle.Contains(mouse.Position) && mouse.RightButton == ButtonState.Pressed);
        }
        /// <summary>
        /// Checks if the sprite image is left-clicked.
        /// </summary>
        /// <param name="mouse">Mouse input struct</param>
        /// <returns></returns>
        public bool LeftClicked(MouseState mouse)
        {
            return (DrawingRectangle.Contains(mouse.Position) && mouse.LeftButton == ButtonState.Pressed);
        }
        /// <summary>
        /// Unloads the texture.
        /// </summary>
        public override void Unload()
        {
            Texture.Dispose();
        }

        /// <summary>
        /// Loads a Sprite object from the file buffer.
        /// </summary>
        /// <param name="buff"></param>
        /// <param name="position"></param>
        /// <param name="result"></param>
        public override void LoadF(byte[] buff, ref int position, out IGameObject result)
        {
            string name = ByteCodeParser.GetString(buff, ref position);
            bool visible = ByteCodeParser.GetBool(buff,ref position);
            string asset = ByteCodeParser.GetString(buff, ref position);
            Vector2 pos = ByteCodeParser.GetVector2(buff, ref position);
            Vector3 rot = ByteCodeParser.GetVector3(buff, ref position);
            Vector2 scal = ByteCodeParser.GetVector2(buff, ref position);
            Color mask = ByteCodeParser.GetColor(buff, ref position);
            result = new Sprite(name,visible,asset,pos,rot.X,new Vector2(rot.Y,rot.Z),scal,mask);
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
            ByteCodeParser.SetVector2(buff, Position);
            ByteCodeParser.SetVector3(buff, new Vector3(Rotation, RotationCenter.X, RotationCenter.Y));
            ByteCodeParser.SetVector2(buff, Scale);
            ByteCodeParser.SetColor(buff, Mask);
        }
    }
}
