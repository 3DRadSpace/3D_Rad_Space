using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
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
        /// Checks if the object will do anything in the update loop.
        /// </summary>
        public bool Enabled { get; set; }

        /// <summary>
        /// Checks if the object will be visible in the drawing loop.
        /// </summary>
        public bool Visible { get; set; }

        Vector3 _position;
        /// <summary>
        /// Object 3D position in the game-world.
        /// </summary>
        public Vector3 Position
        {
            get { return _position; }
            set { _position = value; }
        }
        Quaternion _rotation;
        /// <summary>
        /// Object rotation.
        /// </summary>
        public Quaternion Rotation
        {
            get { return _rotation; }
            set { _rotation = value; }
        }
        Vector3 _scale;
        /// <summary>
        /// 3D Scale of the object.
        /// </summary>
        public Vector3 Scale
        {
            get { return _scale; }
            set { _scale = value; }
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
        public virtual void Update(ref MouseState input, ref KeyboardState keyboard, GameTime time) { }
        /// <summary>
        /// Draws the game to the ID3D11DeviceContext
        /// </summary>
        /// <param name="time">dt. delta-time</param>
        /// <param name="frustrum">Bounding frustrum for 3D models for GPU optimisation.</param>
        /// <param name="view">View Matrix</param>
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
        public virtual void LoadF(List<byte> buff, ref int position, out IGameObject result) 
        {
            result = null;
        }
        /// <summary>
        /// Saves the game object into a buffer that can be stored in a file.
        /// </summary>
        /// <returns></returns>
        public virtual void SaveF(List<byte> buff, ref int position) { }
    }
}
