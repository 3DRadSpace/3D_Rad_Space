using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Camera class.
    /// </summary>
    public class Camera : GameObject
    {
        /// <summary>
        /// Camera object constructor.
        /// </summary>
        /// <param name="name">Objet name.</param>
        /// <param name="Enabled">If camera is enabled.</param>
        /// <param name="Pos">Position</param>
        /// <param name="Rot">Camera rotation.Also used to calculate the target.</param>
        /// <param name="Targ">Camera Target (Propably not used anymore? )</param>
        /// <param name="UpDir">Camera up direction.</param>
        /// <param name="FOV">Field of view in radians</param>
        /// <param name="nearplane">Minumum draw distance</param>
        /// <param name="farplane">Maximum draw distance</param>
        public Camera(string name, bool Enabled, Vector3 Pos, Vector3 Rot,Vector3 Targ, Vector3 UpDir, float FOV, float nearplane, float farplane)
        {
            Name = name;
            this.Enabled = Enabled;
            Position = Pos;
            Rotation = Rot;
            CameraTarget = Targ;
            CameraRotation = UpDir;
            this.FOV = MathHelper.ToRadians(FOV);
            MinDrawDist = nearplane;
            MaxDrawDist = farplane;
        }
        /// <summary>
        /// Camera object constructor.
        /// </summary>
        /// <param name="name">Objet name.</param>
        /// <param name="Enabled">If camera is enabled.</param>
        /// <param name="Pos">Position</param>
        /// <param name="Rot">Camera rotation.Also used to calculate the target.</param>
        /// <param name="UpDir">Camera up direction.</param>
        /// <param name="FOV">Field of view in radians</param>
        /// <param name="nearplane">Minumum draw distance</param>
        /// <param name="farplane">Maximum draw distance</param>
        public Camera(string name,bool Enabled,Vector3 Pos,Vector3 Rot,Vector3 UpDir,float FOV,float nearplane,float farplane)
        {
            Name = name;
            this.Enabled = Enabled;
            Position = Pos;
            Rotation = Rot;
            CameraTarget = Pos+Vector3.Transform(Vector3.UnitZ+Vector3.UnitY,Matrix.CreateFromYawPitchRoll(Rot.Y,Rot.X,Rot.Y));
            CameraRotation = UpDir;
            this.FOV = MathHelper.ToRadians(FOV);
            MinDrawDist = nearplane;
            MaxDrawDist = farplane;
        }
        /// <summary>
        /// Camera constructor for the editor.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="Pos"></param>
        /// <param name="Target"></param>
        /// <param name="FOV"></param>
        /// <param name="nearplane"></param>
        /// <param name="farplane"></param>
        public Camera(string name,Vector3 Pos,Vector3 Target, float FOV, float nearplane, float farplane)
        {
            Name = name;
            Position = Pos;
            CameraTarget = Target;
            this.FOV = MathHelper.ToRadians(FOV);
            MaxDrawDist = farplane;
            MinDrawDist = nearplane;
        }
        /// <summary>
        /// Empty constructor.
        /// </summary>
        public Camera()
        {
            Name = null;
            Enabled = false;
            Position = Vector3.Zero;
            Rotation = Vector3.Zero;
            CameraTarget = Vector3.Forward;
            CameraRotation = Vector3.Up;
            FOV = MathHelper.ToRadians(45);
            MinDrawDist = 0.01f;
            MaxDrawDist = 500f;
        }

        /// <summary>
        /// Expected to be loaded by the game editor.
        /// </summary>
        public static Model model;
        Vector3 DeltaPos;

        /// <summary>
        /// Loads the object. In this cases, initializes the DeltaPos used when the camera is 'chasing' an object.
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            for (int i = 0; i < Behiavours.Count; i++)
            {
                GameObject obj = Game.GameObjects[Behiavours[i].ObjectID] as GameObject;
                int b = Behiavours[i].BehiavourID;
                if (b == 1)
                {
                    DeltaPos = obj.Position - Position;
                }
            }
            base.Load(content);
        }
        /// <summary>
        /// Drawing code for the editor.
        /// </summary>
        public override void EditorDraw(SpriteBatch spriteBatch,Matrix? view,Matrix? projection)
        {
            Game.DrawModel(model, Matrix.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z) *
            Matrix.CreateTranslation(Position), (Matrix)view, (Matrix)projection);
        }

        /// <summary>
        /// Look at point.
        /// </summary>
        public Vector3 CameraTarget;

        /// <summary>
        /// Camera Rotation. (0,1,0) Is the default.
        /// </summary>
        public Vector3 CameraRotation = new Vector3(0,1,0);

        /// <summary>
        /// Fielf of view (Measured in radians).
        /// </summary>
        public float FOV;

        /// <summary>
        /// Screen size. Used to calculate aspect ratio.
        /// </summary>
        public static Vector2 ScreenSize;

        /// <summary>
        /// Sets the FOV with a degree value
        /// </summary>
        /// <param name="deg">Degrees</param>
        public void SetFOVDegrees(float deg)
        {
            FOV = MathHelper.ToRadians(deg);
        }
        /// <summary>
        /// Converts FOV to degrees.
        /// </summary>
        /// <returns>Degrees</returns>
        public float GetFOVDegrees()
        {
            return MathHelper.ToDegrees(FOV);
        }

        /// <summary>
        /// Near plane distance
        /// </summary>
        public float MinDrawDist;

        /// <summary>
        /// Maximum drawing distance.
        /// </summary>
        public float MaxDrawDist;

        /// <summary>
        /// Updates the Camera object. In this case, the Camera object is affected by it's 'relationships'.
        /// </summary>
        /// <param name="mouse">Not used</param>
        /// <param name="keyboard">Not used</param>
        /// <param name="time">Not used</param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            for (int i = 0; i < Behiavours.Count; i++)
            {
                GameObject obj = Game.GameObjects[Behiavours[i].ObjectID] as GameObject;
                int b = Behiavours[i].BehiavourID;
                if (b == 2)
                {
                    CameraTarget = obj.Position;
                }
                if (b == 1)
                {
                    Position = obj.Position + DeltaPos;
                    CameraTarget = obj.Position;
                }
            }
            base.Update(mouse, keyboard, time);
        }

        /// <summary>
        /// Camera drawing for game code. This method doesn't override the GameObject's Draw function. :thinking:
        /// </summary>
        /// <param name="spriteBatch">Not used.</param>
        /// <param name="view">Uses it's own view</param>
        /// <param name="projection"></param>
        public void Draw(SpriteBatch spriteBatch,out Matrix view,out Matrix projection)
        {
            if (!Enabled)
            {
                view = Matrix.Identity;
                projection = Matrix.Identity;
                return;
            }
            view = Matrix.CreateLookAt(Position, CameraTarget, CameraRotation);
            projection = Matrix.CreatePerspectiveFieldOfView(FOV, ScreenSize.X / ScreenSize.Y,MinDrawDist,MaxDrawDist);
            base.Draw(null,view,projection); //Calls base class to get the event called too.
        }
    }
}
