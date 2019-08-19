using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System;

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
        /// <param name="Target">Camera look at.</param>
        /// <param name="UpDir">Camera up direction.</param>
        /// <param name="FOV">Field of view in radians</param>
        /// <param name="nearplane">Minumum draw distance</param>
        /// <param name="farplane">Maximum draw distance</param>
        public Camera(string name,bool Enabled,Vector3 Pos,Vector3 Target,Vector3 UpDir,float FOV,float nearplane,float farplane)
        {
            Name = name;
            this.Enabled = Enabled;
            Position = Pos;
            CameraTarget = Target;
            CameraRotation = UpDir;
            this.FOV = FOV;
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
            this.FOV = FOV;
            MaxDrawDist = farplane;
            MinDrawDist = nearplane;
        }
        /// <summary>
        /// Expected to be loaded by the game editor.
        /// </summary>
        public static Model model;
        /// <summary>
        /// Drawing code for the editor.
        /// </summary>
        public override void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (view == null) throw new ArgumentNullException("view", "Matrix view was null, drawing cannot be done.");
            if (projection == null) throw new ArgumentNullException("projection", "Projection Matrix is null, cannot draw the model.");
            Game.DrawModel(model, Matrix.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z) *
                Matrix.CreateTranslation(Position), (Matrix)view, (Matrix)projection);
        }
        /// <summary>
        /// Camera view matrix
        /// </summary>
        public Matrix View;
        /// <summary>
        /// Camera projection matrix.
        /// </summary>
        public Matrix Projection;

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
        /// Camera drawing for game code.
        /// </summary>
        /// <param name="spriteBatch">Not used.</param>
        /// <param name="view">Uses it's own view;</param>
        /// <param name="projection"></param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (!Enabled) return;
            View = Matrix.CreateLookAt(Position, CameraTarget, CameraRotation);
            Projection = Matrix.CreatePerspectiveFieldOfView(FOV, ScreenSize.X / ScreenSize.Y,MinDrawDist,MaxDrawDist);
            base.Draw(null, View, Projection); //Calls base class to get the event called too.
        }
    }
}
