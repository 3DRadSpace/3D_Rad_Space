using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Represents a First person view camera.
    /// </summary>
    public class FPVCamera : Camera
    {
        /// <summary>
        /// Camera rotation coordinates related to screen.
        /// </summary>
        public Vector2 CamScreenCoords;
        /// <summary>
        /// Vertical rotaition bounds.
        /// </summary>
        public float Bound;
        /// <summary>
        /// Movement speed.
        /// </summary>
        public float MovementSpeed;
        /// <summary>
        /// Mouse sensiblity.
        /// </summary>
        public float Sensibility;

        /// <summary>
        /// Forward movment key.
        /// </summary>
        Keys Forward;
        /// <summary>
        /// Back movment key.
        /// </summary>
        Keys Backward;
        /// <summary>
        /// Left movment key.
        /// </summary>
        Keys Left;
        /// <summary>
        /// Right movment key.
        /// </summary>
        Keys Right;
        
        /// <summary>
        /// Default constructor.
        /// </summary>
        public FPVCamera()
        {
            Bound = MathHelper.Pi - 0.1f;
            Forward = Keys.W;
            Backward = Keys.S;
            Right = Keys.D;
            Left = Keys.A;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="pos"></param>
        /// <param name="up"></param>
        /// <param name="look_coords"></param>
        /// <param name="fov"></param>
        public FPVCamera(string name,bool enabled,Vector3 pos,Vector3 up,Vector2 look_coords,float fov)
        {
            Name = name;
            Enabled = enabled;
            Position = pos;
            CameraRotation = up;
            Bound = MathHelper.Pi - 0.1f;
            Forward = Keys.W;
            Backward = Keys.S;
            Right = Keys.D;
            Left = Keys.A;
            CamScreenCoords = look_coords;
            FOV = fov;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="spriteBatch"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (Keyboard.GetState().IsKeyDown(Forward)) Position += Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y)) * MovementSpeed;
            if (Keyboard.GetState().IsKeyDown(Backward)) Position -= Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y)) * MovementSpeed;
            if (Keyboard.GetState().IsKeyDown(Right)) Position += Vector3.Cross(CameraTarget, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y))) * MovementSpeed;
            if (Keyboard.GetState().IsKeyDown(Left)) Position -= Vector3.Cross(CameraTarget, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y))) * MovementSpeed;

            MouseState mouse = Mouse.GetState();

            if (mouse.RightButton == ButtonState.Pressed)
            {
                if (mouse.X >= 0 && mouse.X <= ScreenSize.X && mouse.Y >= 0 && mouse.Y <= ScreenSize.Y)
                {
                    Mouse.SetPosition((int)ScreenSize.X / 2,(int) ScreenSize.Y / 2);
                    CamScreenCoords += new Vector2((mouse.X - (ScreenSize.X / 2)) * (-Sensibility), (mouse.Y - (ScreenSize.Y / 2)) * Sensibility);
                    if (CamScreenCoords.Y > (MathHelper.Pi - 0.1f)) CamScreenCoords.Y = (MathHelper.Pi - 0.1f);
                    if (CamScreenCoords.Y < 0) CamScreenCoords.Y = 0.1f;
                }
            }
            base.Draw(spriteBatch, view, projection);
        }
    }
}
