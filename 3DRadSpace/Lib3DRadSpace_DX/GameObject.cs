using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BEPUphysics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Base class for alll 'game-objects' containing common implementation of fields and functions.
    /// </summary>
    public abstract class BaseGameObject : IGameObject
    {
        string _name;
        /// <summary>
        /// Object name. Spaces will be removed.
        /// </summary>
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                value?.Trim(' ');
                _name = value;
            }
        }
        /// <summary>
        /// Checks if the object will cycle it's update loop.
        /// </summary>
        public bool Enabled;
        /// <summary>
        /// Checks if the object is visible or not.
        /// </summary>
        public bool Visible;

        /// <summary>
        /// Object 3D position in the game-world.
        /// </summary>
        public Vector3 Position;

        /// <summary>
        /// Object rotation.
        /// </summary>
        public Quaternion Rotation
        {
            get
            {
                return _rotation;
            }
            set
            {
                _rotation = value;
                //TODO: Set the Euler Angle rotation.
            }
        }
        Quaternion _rotation;

        /// <summary>
        /// Rotation euler 
        /// </summary>
        public Vector3 RotationEuler
        {
            set
            {
                _rotation = Quaternion.CreateFromYawPitchRoll(value.Y, value.X, value.Z);
            }
            get
            {
                return Maths.QuaternionToVector3(_rotation);
            }
        }
        /// <summary>
        /// 3D Scale of the object.
        /// </summary>
        public Vector3 Scale;

        /// <summary>
        /// Specifies the rotation center
        /// </summary>
        public Vector3 RotationCenter;

        /// <summary>
        /// Asset file name. May differ from object to object.
        /// </summary>
        public string Asset;

        /// <summary>
        /// Gets the World matrix, passed to shaders as a argument.
        /// </summary>
        public Matrix World
        {
            get
            {
                return Matrix.CreateScale(Scale) * Matrix.CreateTranslation(RotationCenter) * Matrix.CreateFromQuaternion(_rotation) * Matrix.CreateTranslation(Position);
            }
        }

        /// <summary>
        /// Loads the object.
        /// </summary>
        public virtual void Load(ContentManager content) { }

        /// <summary>
        /// Updates the physics and input logic.
        /// </summary>
        /// <param name="input">Mouse input. Passed by reference, for the sake of optimisation.</param>
        /// <param name="keyboard">Keyboard input. Passed by reference, for the sake of speed. Microptimisation :TM:</param>
        /// <param name="time">dt. delta-time</param>
        public virtual void Update(ref MouseState input, ref KeyboardState keyboard, GameTime time)
        {
            if(RunOnce) RunOnce = false;
        }
        /// <summary>
        /// Draws the "game-object" to the ID3D11DeviceContext
        /// </summary>
        /// <param name="time">dt. delta-time</param>
        /// <param name="frustrum">Bounding frustrum for 3D models for GPU optimisation.</param>
        /// <param name="view">View Matrix. Represents the camera's coordinates</param>
        /// <param name="projection">Projection Matrix.</param>
        public virtual void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection) { }
        /// <summary>
        /// Debug draw. Specific to the game engine editor(s).
        /// </summary>
        /// <param name="time">dt. Delta Time. Except it won't be propably used.</param>
        /// <param name="frustrum">Bounding frustrum allowing a specific drawing optimisation.</param>
        /// <param name="view">View Matrix</param>
        /// <param name="projection">Projection Matrix.</param>
        public virtual void EditorDraw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection) { }
        /// <summary>
        /// Loads the game object from a file buffer.
        /// </summary>
        /// <param name="buff">file buffer</param>
        /// <param name="position">Buffer position</param>
        /// <param name="result">Loaded IGameObject. Null if failed.</param>
        public virtual void LoadF(byte[] buff, ref int position, out IGameObject result) 
        {
            result = null;
        }
        /// <summary>
        /// Saves the game object into a buffer that can be stored in a file.
        /// </summary>
        /// <returns></returns>
        public virtual void SaveF(List<byte> buff) { }

        /// <summary>
        /// List of editor selected behiavours.
        /// </summary>
        public List<BehiavourStruct> Behiavours;

        /// <summary>
        /// Triggers the object's action.
        /// </summary>
        public virtual void Trigger()
        {
            Enabled = true;
        }

        /// <summary>
        /// Unloads native resources.
        /// </summary>
        public virtual void Unload()
        {
            
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="ray"></param>
        /// <returns></returns>
        public virtual Vector3? RayIntersection(Ray ray)
        {
            return null;
        }

        /// <summary>
        /// Initializes the object's physics.
        /// </summary>
        /// <param name="space"></param>
        public virtual void PhysicsInitialize(Space space)
        {

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="time"></param>
        /// <param name="batch"></param>
        public virtual void Draw2D(GameTime time, SpriteBatch batch)
        {

        }
        /// <summary>
        /// 
        /// </summary>
        public bool RunOnce = true;
    }
}
