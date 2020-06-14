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
        public Keys Forward;
        /// <summary>
        /// Back movment key.
        /// </summary>
        public Keys Backward;
        /// <summary>
        /// Left movment key.
        /// </summary>
        public Keys Left;
        /// <summary>
        /// Right movment key.
        /// </summary>
        public Keys Right;
        
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
            Bound = MathHelper.Pi - 0.1f;
        }
        /// <summary>
        /// Main camera constructor.
        /// </summary>
        /// <param name="name">Editor name.</param>
        /// <param name="enabled">Enables drawing or not.</param>
        /// <param name="pos">World position,</param>
        /// <param name="look_coords">View coordinates</param>
        /// <param name="up">Up vector</param>
        /// <param name="fov">Field of view in radians.</param>
        /// <param name="nearplane">Minimum draw distance.</param>
        /// <param name="farplane">Maximum draw distance.</param>
        /// <param name="w">Forward key</param>
        /// <param name="a">Left key</param>
        /// <param name="s">Backward key</param>
        /// <param name="d">Right key</param>
        /// <param name="mov_speed">Movement speed.</param>
        /// <param name="rot_speed">Rotation speed</param>
        public FPVCamera(string name, bool enabled, Vector3 pos, Vector2 look_coords, Vector3 up, float fov, float nearplane, float farplane, Keys w,Keys a,Keys s,Keys d,float mov_speed,float rot_speed)
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
            MinDrawDist = nearplane;
            MaxDrawDist = farplane;
            Forward = w;
            Backward = s;
            Right = d;
            Left = a;
            Bound = MathHelper.Pi - 0.1f;
            MovementSpeed = mov_speed;
            Sensibility = rot_speed;
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
            if (keyboard.IsKeyDown(Right)) Position -= Vector3.Cross(Vector3.Up, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y))) * MovementSpeed;
            if (keyboard.IsKeyDown(Left)) Position += Vector3.Cross(Vector3.Up, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y))) * MovementSpeed;

            Mouse.SetPosition((int)ScreenSize.X / 2,(int) ScreenSize.Y / 2);
            CamScreenCoords += new Vector2((mouse.X - (ScreenSize.X / 2)) * (-Sensibility), (mouse.Y - (ScreenSize.Y / 2)) * Sensibility);
            if (CamScreenCoords.Y > (MathHelper.Pi - 0.01f)) CamScreenCoords.Y = (MathHelper.Pi - 0.01f);
            if (CamScreenCoords.Y < 0) CamScreenCoords.Y = 0.01f;
            CameraTarget = Position + Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CamScreenCoords.X, 0, CamScreenCoords.Y));
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public void Draw(out Matrix view, out Matrix projection)
        {
            if (!Enabled)
            {
                view = Matrix.Identity;
                projection = Matrix.Identity;
                return;
            }
            view = Matrix.CreateLookAt(Position, CameraTarget, Vector3.Up);
            projection = Matrix.CreatePerspectiveFieldOfView(FOV, ScreenSize.X / ScreenSize.Y, MinDrawDist, MaxDrawDist);
            base.Draw(null, view, projection); //Calls base class to get the event called too.
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
        /// <summary>
        /// 
        /// </summary>
        public void SetWASDConfig()
        {
            Forward = Keys.W;
            Backward = Keys.S;
            Right = Keys.D;
            Left = Keys.A;
        }
        /// <summary>
        /// 
        /// </summary>
        public void SetArrowConfig()
        {
            Forward = Keys.Up;
            Backward = Keys.Down;
            Right = Keys.Right;
            Left = Keys.Left;
        }
    }
}
