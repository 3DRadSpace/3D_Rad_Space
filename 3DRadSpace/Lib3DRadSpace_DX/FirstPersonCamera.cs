using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using BEPUphysics.Character;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Class representing a first person camera allowing looking around and moving on the map, jumping, crouching, and staying prone.
    /// This class is not inhereted from the Camera object, because levels of inheritance will slow down the performance of the game project.
    /// The OOP nature of 3DRadSpace + the fact that 3DRadSpace is bulid from Monogame instead of DirectX 11/12 or OpenGL are already big enough slowdowns.
    /// </summary>
    public class FirstPersonCamera : BaseGameObject
    {
        /// <summary>
        /// FPCamera main constructor containing all the arguments.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="pos"></param>
        /// <param name="look"></param>
        /// <param name="norm"></param>
        /// <param name="npd"></param>
        /// <param name="fpd"></param>
        /// <param name="speed"></param>
        /// <param name="sensibility"></param>
        /// <param name="height"></param>
        public FirstPersonCamera(string name = "Name",bool enabled = true,Vector3 pos=default,Vector2 look=default,Vector3 norm=default,float npd = 0.01f,float fpd = 500.0f,float speed = 5f,float height = 1.7f,float sensibility = 1f)
        {
            Name = name;
            Enabled = enabled;
            Position = pos;
            Look_At = look;
            Normal = norm;
            NearPlaneDistance = npd;
            FarPlaneDistance = fpd;
            Height = height;
            Sensibility = sensibility;
            _controller = new CharacterController(BEPU2XNA.CvVec(pos), height);
        }
        CharacterController _controller;
        /// <summary>
        /// Contains the rotation degrees given by the input.
        /// </summary>
        public Vector2 Look_At;
        /// <summary>
        /// Represents the camera's rotation in a unit vector.
        /// </summary>
        public Vector3 LookDir;
        /// <summary>
        /// 
        /// </summary>
        public Vector3 Normal;

        /// <summary>
        /// Minimum drawing distance.
        /// </summary>
        public float NearPlaneDistance;
        /// <summary>
        /// Maximum drawing distance.
        /// </summary>
        public float FarPlaneDistance;

        /// <summary>
        /// Character movement speed.
        /// </summary>
        public float MovmentSpeed
        {
            get
            {
                return 0;
            }
            set
            {

            }
        }
        /// <summary>
        /// Character height.
        /// </summary>
        public float Height
        {
            get
            {
                return 0;
            }
            set
            {

            }
        }
        /// <summary>
        /// Represents mouse->character rotation movment speed.
        /// </summary>
        public float Sensibility;

        /// <summary>
        /// Represents the camera height when crouching.
        /// </summary>
        public float CrouchingHeight
        {
            get
            {
                return 0;
            }
            set
            {

            }
        }
        /// <summary>
        /// represents the camera height when staying in a prone position.
        /// </summary>
        public float ProneHeight
        {
            get
            {
                return 0;
            }
            set
            {

            }
        }
        /// <summary>
        /// 
        /// </summary>
        public bool Render2DSprites;

        /// <summary>
        /// Represents the stances of the character.
        /// Other values can represent custom stances, like crouching + peeking a wall (like in Insurgency)
        /// Since this is a byte, a total of 255 stances can be implemented.
        /// Default values are:
        /// 0 - Default
        /// 1 - Crouching
        /// 2 - Prone
        /// </summary>
        public byte Stance
        {
            get
            {
                return 0;
            }
            set
            {

            }
        }

        /// <summary>
        /// Represents the camera's field of view (FoV) in radians.
        /// </summary>
        public float FOV;

        /// <summary>
        /// Defines the forward movment key.
        /// </summary>
        public Keys Key_Forward;
        /// <summary>
        /// Defines the backward movment key.
        /// </summary>
        public Keys Key_Backwards;
        /// <summary>
        /// Defines the left movment key.
        /// </summary>
        public Keys Key_Left;
        /// <summary>
        /// Defines the right movment key.
        /// </summary>
        public Keys Key_Right;
        /// <summary>
        /// Defines the jump key.
        /// </summary>
        public Keys Key_Jump;
        /// <summary>
        /// Defines the crouch key.
        /// </summary>
        public Keys Key_Crouch;
        /// <summary>
        /// Defines the prone key.
        /// </summary>
        public Keys Key_Prone;
        /// <summary>
        /// Defines the sprinting key.
        /// </summary>
        public Keys Key_Sprint;

        /// <summary>
        /// Updates the matrices used when drawing 3D elements.
        /// </summary>
        /// <param name="time">DT value</param>
        /// <param name="frustrum">Not used.</param>
        /// <param name="view">Output value</param>
        /// <param name="projection">Output value.</param>
        public override void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            view = Matrix.CreateLookAt(Position, Position + LookDir, Normal);
            projection = Matrix.CreatePerspectiveFieldOfView(FOV, 0, NearPlaneDistance, FarPlaneDistance);
        }
        /// <summary>
        /// Handles the camera rotation by taking the mouse as input.
        /// </summary>
        /// <param name="input"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(ref MouseState input, ref KeyboardState keyboard, GameTime time)
        {
            float dt = (float)time.ElapsedGameTime.TotalSeconds;
            float dt2 = dt * dt;

            float mx=0, my=0;
            Mouse.SetPosition((int)mx, (int)my); //TODO: get the middle point.
            float dx = mx - input.X;
            float dy = my - input.Y;

            Look_At += (new Vector2(dx * dt2, dy * dt2)) * Sensibility;

            LookDir = new Vector3((float)Math.Sin(Look_At.X), (float)Math.Tan(Look_At.Y),(float) Math.Cos(Look_At.X));
            _controller.ViewDirection = BEPU2XNA.CvVec(LookDir);

            BEPUutilities.Vector2 movsum = BEPUutilities.Vector2.Zero;
            if(keyboard.IsKeyDown(Key_Forward)) movsum += BEPUutilities.Vector2.UnitY;
            if(keyboard.IsKeyDown(Key_Backwards)) movsum -= BEPUutilities.Vector2.UnitY;
            if(keyboard.IsKeyDown(Key_Left)) movsum -= BEPUutilities.Vector2.UnitX;
            if(keyboard.IsKeyDown(Key_Right)) movsum += BEPUutilities.Vector2.UnitX;
            if(keyboard.IsKeyDown(Key_Jump)) _controller.Jump();

            if(keyboard.IsKeyDown(Keys.LeftShift) || keyboard.IsKeyDown(Keys.RightShift))
            {
                if(_controller.StanceManager.DesiredStance == BEPUphysics.Character.Stance.Standing) _controller.StandingSpeed = 12;
            }
            else _controller.StandingSpeed = 8;
            if(keyboard.IsKeyDown(Keys.C)) _controller.StanceManager.DesiredStance = BEPUphysics.Character.Stance.Crouching;
            else _controller.StanceManager.DesiredStance = BEPUphysics.Character.Stance.Standing;

            BEPUutilities.Vector2 movf = BEPUutilities.Vector2.Zero;
            if(movsum.LengthSquared() != 0) movf = BEPUutilities.Vector2.Normalize(movsum);

            _controller.HorizontalMotionConstraint.MovementDirection = movf;

            base.Update(ref input, ref keyboard, time);
        }
    }
}
