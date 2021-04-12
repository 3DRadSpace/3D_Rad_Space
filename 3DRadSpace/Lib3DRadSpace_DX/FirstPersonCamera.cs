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
    /// A class representing a first person camera allowing looking around and moving on the map, jumping, crouching, and staying prone.
    /// This class is not inhereted from the Camera object, because levels of inheritance will slow down the performance of the game project.
    /// The OOP nature of 3DRadSpace + the fact that 3DRadSpace is bulid from Monogame instead of pure DirectX 11/12 or OpenGL are already big enough slowdowns.
    /// </summary>
    public class FirstPersonCamera : BaseGameObject
    {
        /// <summary>
        /// FirstPersonCamera constructor. Provides all the necessary initialization arguments.
        /// </summary>
        /// <param name="name">Name of the object</param>
        /// <param name="enabled">Checks if the object will do physics + rendering logic (setting the view and projection matrices)</param>
        /// <param name="pos">Location in the 3D coordinates</param>
        /// <param name="look">A normalized vector defining the characters's direction.</param>
        /// <param name="norm">Camera's UP direction.</param>
        /// <param name="npd">Minimum render frustrum distance.</param>
        /// <param name="fpd">Maximum render frustrum distance.</param>
        /// <param name="speed">Base movment speed</param>
        /// <param name="sensibility">Mouse sensibility</param>
        /// <param name="height">Defines the character's height</param>
        /// <param name="crouchingHeight">Defines the camera height at the crouching stance</param>
        /// <param name="proneHeight">Defines the camera height at the prone stance</param>
        /// <param name="crouchingspeed">Defines the movment speed in the crouching stance</param>
        /// <param name="pronespeed">Defines the movement speed in the prone stance</param>
        /// <param name="runningspeed">Defines the running speed.</param>
        /// <param name="mass">Defines the mass of the character's body</param>
        /// <param name="backward">Keyboard key defining the backward movement</param>
        /// <param name="forward">Keyboard key defining the forward movement</param>
        /// <param name="left">Keyboard key defining the left movement</param>
        /// <param name="right">Keyboard key defining the rights movement</param>
        /// <param name="crouch">Chrouching key</param>
        /// <param name="sprint">Sprinting key</param>
        /// <param name="prone">Sprinting key</param>
        /// <param name="fov">Field of view in radians. Default value is ~65 degrees.</param>
        /// <param name="jmp">Jumping key</param>
        public FirstPersonCamera(string name = "Name",bool enabled = true,Vector3 pos=default,Vector3 look=default,Vector3 norm=default,float npd = 0.01f,float fpd = 500.0f,float fov= 1.1344641f, float mass = 10,float speed = 8f,float runningspeed=12f,float crouchingspeed=3,float pronespeed=1.5f,float height = 1.7f,float crouchingHeight=1.19f,float proneHeight= 0.51000005F, float sensibility = 1f, Keys forward = Keys.Up,Keys backward = Keys.Down, Keys right = Keys.Right,Keys left = Keys.Left,Keys crouch = Keys.C,Keys prone = Keys.Z,Keys sprint = Keys.LeftShift,Keys jmp = Keys.Space )
        {
            Name = name;
            Enabled = enabled;
            Position = pos;
            LookDir = look;
            Normal = norm;
            NearPlaneDistance = npd;
            FarPlaneDistance = fpd;
            Sensibility = sensibility;
            SprintSpeed = runningspeed;
            FOV = fov;
            _controller = new CharacterController(BEPU2XNA.CvVec(pos), height,crouchingHeight,proneHeight,0.6f,0.1f,mass,0.8f,1.3f,speed,crouchingspeed,pronespeed);
            _controller.ViewDirection = BEPU2XNA.CvVec(new Vector3(look.X,0,look.Y));
            Key_Forward = forward;
            Key_Backwards = backward;
            Key_Left = left;
            Key_Right = right;
            Key_Crouch = crouch;
            Key_Prone = prone;
            Key_Jump = jmp;
            Key_Sprint = sprint;
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
                return _controller.StandingSpeed;
            }
            set
            {
                _controller.StandingSpeed = value;
            }
        }
        /// <summary>
        /// Gets or sets the crouching speed.
        /// </summary>
        public float CrouchingSpeed
        {
            get
            {
                return _controller.CrouchingSpeed;
            }
            set
            {
                _controller.CrouchingSpeed = value;
            }
        }

        /// <summary>
        /// Gets or sets the prone movement speed.
        /// </summary>
        public float ProneSpeed
        {
            get
            {
                return _controller.ProneSpeed;
            }
            set
            {
                _controller.ProneSpeed = value;
            }
        }

        /// <summary>
        /// Character running speed.
        /// </summary>
        public float SprintSpeed;

        /// <summary>
        /// Represents mouse->character rotation movment speed.
        /// </summary>
        public float Sensibility;


        /// <summary>
        /// 
        /// </summary>
        public float Height
        {
            get
            {
                return _controller.StanceManager.StandingHeight;
            }
            set
            {
                _controller.StanceManager.StandingHeight = value;
            }
        }

        /// <summary>
        /// Represents the camera height when crouching.
        /// </summary>
        public float CrouchingHeight
        {
            get
            {
                return _controller.StanceManager.CrouchingHeight;
            }
            set
            {
                _controller.StanceManager.CrouchingHeight = value;
            }
        }
        /// <summary>
        /// represents the camera height when staying in a prone position.
        /// </summary>
        public float ProneHeight
        {
            get
            {
                return _controller.StanceManager.ProneHeight;
            }
            set
            {
                _controller.StanceManager.ProneHeight = value;
            }
        }

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
                return (byte)_controller.StanceManager.CurrentStance;
            }
            set
            {
                _controller.StanceManager.DesiredStance = (BEPUphysics.Character.Stance)value;
            }
        }

        /// <summary>
        /// Represents the camera's field of view (FoV) in radians.
        /// </summary>
        public float FOV;

        /// <summary>
        /// Defines the mass of the character's body.
        /// </summary>
        public float Mass
        {
            get
            {
                return _controller.Body.Mass;
            }
            set
            {
                _controller.Body.Mass = value;
            }
        }

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
            projection = Matrix.CreatePerspectiveFieldOfView(FOV, CurrentProject.Resolution.X / CurrentProject.Resolution.Y, NearPlaneDistance, FarPlaneDistance);
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

            float mx= CurrentProject.Resolution.X/2, my= CurrentProject.Resolution.Y / 2;
            Mouse.SetPosition((int)mx, (int)my); //TODO: get the middle point.
            float dx = mx - input.X;
            float dy = my - input.Y;

            Look_At += (new Vector2(dx * dt2, -dy * dt2)) * Sensibility;

            LookDir = Vector3.Transform(Vector3.UnitZ, Quaternion.CreateFromYawPitchRoll(Look_At.X, 0, 0) * Quaternion.CreateFromYawPitchRoll(0, Look_At.Y, 0));
            _controller.ViewDirection = BEPU2XNA.CvVec(LookDir);

            BEPUutilities.Vector2 movsum = BEPUutilities.Vector2.Zero;
            if(keyboard.IsKeyDown(Key_Forward)) movsum += BEPUutilities.Vector2.UnitY;
            if(keyboard.IsKeyDown(Key_Backwards)) movsum -= BEPUutilities.Vector2.UnitY;
            if(keyboard.IsKeyDown(Key_Left)) movsum -= BEPUutilities.Vector2.UnitX;
            if(keyboard.IsKeyDown(Key_Right)) movsum += BEPUutilities.Vector2.UnitX;
            if(keyboard.IsKeyDown(Key_Jump)) _controller.Jump();

            if(keyboard.IsKeyDown(Keys.LeftShift) || keyboard.IsKeyDown(Keys.RightShift))
            {
                if(_controller.StanceManager.DesiredStance == BEPUphysics.Character.Stance.Standing) _controller.StandingSpeed = SprintSpeed;
            }
            else _controller.StandingSpeed = MovmentSpeed;
            if(keyboard.IsKeyDown(Key_Crouch)) _controller.StanceManager.DesiredStance = BEPUphysics.Character.Stance.Crouching;
            else _controller.StanceManager.DesiredStance = BEPUphysics.Character.Stance.Standing;

            BEPUutilities.Vector2 movf = BEPUutilities.Vector2.Zero;
            if(movsum.LengthSquared() != 0) movf = BEPUutilities.Vector2.Normalize(movsum);

            _controller.HorizontalMotionConstraint.MovementDirection = movf;
        }
        /// <summary>
        /// Checks if (an approximation of the hitbox) intersects the given ray
        /// </summary>
        /// <param name="ray"></param>
        /// <returns></returns>
        public override float? RayIntersection(Ray ray)
        {
            return ray.Intersects(new BoundingSphere(Position, Height));
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
            bool enabled = ByteCodeParser.GetBool(buff, ref position);
            Vector3 pos = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 look_dir = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 norm = ByteCodeParser.GetVector3(buff,ref position);
            Vector3 d1 = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 d2 = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 d3 = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 d4 = ByteCodeParser.GetVector3(buff, ref position);
            Keys w = ByteCodeParser.GetKey(buff, ref position);
            Keys s = ByteCodeParser.GetKey(buff, ref position);
            Keys d = ByteCodeParser.GetKey(buff, ref position);
            Keys a = ByteCodeParser.GetKey(buff, ref position);
            Keys c = ByteCodeParser.GetKey(buff, ref position);
            Keys z = ByteCodeParser.GetKey(buff, ref position);
            Keys jmp = ByteCodeParser.GetKey(buff, ref position);
            result = new FirstPersonCamera(name, enabled, pos, look_dir, norm, d1.X, d1.Y, d1.Z, d2.X, d2.Y, d2.Z, d3.X, d3.Y, d3.Z, d4.X, d4.Y,d4.Z,w,s,d,a,c,z,jmp);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        public override void SaveF(List<byte> buff)
        {
            ByteCodeParser.SetString(buff, Name);
            ByteCodeParser.SetBool(buff, Enabled);
            ByteCodeParser.SetVector3(buff, Position);
            ByteCodeParser.SetVector3(buff, LookDir);
            ByteCodeParser.SetVector3(buff, Normal);
            ByteCodeParser.SetVector3(buff, new Vector3(NearPlaneDistance,FarPlaneDistance,FOV));
            ByteCodeParser.SetVector3(buff, new Vector3(Mass,MovmentSpeed,SprintSpeed));
            ByteCodeParser.SetVector3(buff, new Vector3(CrouchingSpeed,ProneSpeed,Height));
            ByteCodeParser.SetVector3(buff, new Vector3(CrouchingHeight,ProneHeight,Sensibility));
            ByteCodeParser.SetKey(buff, Key_Forward);
            ByteCodeParser.SetKey(buff, Key_Backwards);
            ByteCodeParser.SetKey(buff, Key_Right);
            ByteCodeParser.SetKey(buff, Key_Left);
            ByteCodeParser.SetKey(buff, Key_Crouch);
            ByteCodeParser.SetKey(buff, Key_Prone);
            ByteCodeParser.SetKey(buff, Key_Jump);
            base.SaveF(buff);
        }
    }
}
