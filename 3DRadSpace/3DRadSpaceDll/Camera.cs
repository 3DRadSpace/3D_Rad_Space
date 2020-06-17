using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// 3D Camera class. Allows drawing three dimensinal scenes.
    /// </summary>
    public class Camera : GameObject
    {
        /// <summary>
        /// Camera object constructor.
        /// </summary>
        /// <param name="name">Object name.</param>
        /// <param name="Enabled">If camera is enabled.</param>
        /// <param name="Pos">Camera position.</param>
        /// <param name="Rot">Camera rotation. Also used to calculate the target.</param>
        /// <param name="Targ">Camera Target. The point the camera is looking at.</param>
        /// <param name="UpDir">Camera up direction.</param>
        /// <param name="FOV">Field of view in radians.</param>
        /// <param name="nearplane">Minumum draw distance.</param>
        /// <param name="farplane">Maximum draw distance.</param>
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
            Behiavours = new System.Collections.Generic.List<ObjectBehiavour>();
        }
        /// <summary>
        /// Creates a Camera object with the specified arguments.
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
            CameraTarget = Pos+Vector3.Transform(Vector3.UnitZ,Matrix.CreateFromYawPitchRoll(Rot.Y,Rot.X,Rot.Y));
            CameraRotation = UpDir;
            this.FOV = MathHelper.ToRadians(FOV);
            MinDrawDist = nearplane;
            MaxDrawDist = farplane;
            Behiavours = new System.Collections.Generic.List<ObjectBehiavour>();
        }
        /// <summary>
        /// Camera constructor used in the editor.
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
            Behiavours = new System.Collections.Generic.List<ObjectBehiavour>();
        }
        /// <summary>
        /// Empty constructor. Values are mostly default.
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
            Behiavours = new System.Collections.Generic.List<ObjectBehiavour>();
        }

        /// <summary>
        /// Expected to be loaded by the game editor. Not used in 3DRadSpacePlayer.
        /// </summary>
        public static Model model;
        /// <summary>
        /// Difference between 'chased object' and Camera position.
        /// </summary>
        Vector3 DeltaPos;

        /// <summary>
        /// Loads the object. In this cases, initializes the DeltaPos used when the camera is 'chasing' an object.
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            if (Behiavours != null)
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
        /// Camera Rotation. This is a normalized 3D Vector (with the lenght equal to 1)
        /// </summary>
        public Vector3 CameraRotation;

        /// <summary>
        /// Field of view (Measured in radians).
        /// </summary>
        public float FOV;

        /// <summary>
        /// Screen size. Used to calculate the projection's aspect ratio.
        /// </summary>
        public static Vector2 ScreenSize;

        /// <summary>
        /// Field of view angle in degrees.
        /// </summary>
        public float FOVDegrees
        {
            get
            {
                return MathHelper.ToDegrees(FOV);
            }
            set
            {
                FOV = MathHelper.ToRadians(value);
            }
        }


        /// <summary>
        /// Minimum drawing distance. A recommended value is 0.1f.
        /// </summary>
        public float MinDrawDist;

        /// <summary>
        /// Maximum drawing distance.
        /// </summary>
        public float MaxDrawDist;

        /// <summary>
        /// Updates the Camera object. In this case, the Camera object is affected by it's 'relationship(s)'.
        /// </summary>
        /// <param name="mouse">Not used</param>
        /// <param name="keyboard">Not used</param>
        /// <param name="time">Not used</param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            if (!Enabled) return;
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
        /// <param name="view">Uses it's own view</param>
        /// <param name="projection"></param>
        public void Draw(out Matrix view,out Matrix projection)
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
