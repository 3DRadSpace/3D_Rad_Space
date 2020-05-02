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
        /// <param name="mouse"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            if (keyboard.IsKeyDown(Forward)) Position += Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y)) * MovementSpeed;
            if (keyboard.IsKeyDown(Backward)) Position -= Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y)) * MovementSpeed;
            if (keyboard.IsKeyDown(Right)) Position += Vector3.Cross(CameraTarget, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y))) * MovementSpeed;
            if (keyboard.IsKeyDown(Left)) Position -= Vector3.Cross(CameraTarget, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y))) * MovementSpeed;

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
            base.Update(mouse, keyboard, time);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="spriteBatch"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            Game.DrawModel(EventOnLocation.Sphere, Matrix.CreateScale(2f) * Matrix.CreateTranslation(Position),view.Value,projection.Value);
            Game.DrawModel(model, Matrix.CreateTranslation(Position + new Vector3(1f, 1.8f, 0.5f)),view.Value,projection.Value);
        }
    }
}
