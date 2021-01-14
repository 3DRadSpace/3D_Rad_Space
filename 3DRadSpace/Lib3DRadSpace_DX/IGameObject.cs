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
    /// Absolute base interface for all of the "game-objects" in 3DRadSpace.
    /// Specific objects will have their own specific function overloading for the Update()/Draw() functions
    /// </summary>
    public interface IGameObject
    {
        /// <summary>
        /// Object name.
        /// </summary>
        string Name { get; set; }

        /// <summary>
        /// Represents the asset file the object is using.
        /// </summary>
        string Asset { get; set; }

        /// <summary>
        /// Checks if the object will do anything in the update loop.
        /// </summary>
        bool Enabled { get; set; }

        /// <summary>
        /// Checks if the object will be visible in the drawing loop.
        /// </summary>
        bool Visible { get; set; }

        /// <summary>
        /// Object 3D position in the game-world.
        /// </summary>
        Vector3 Position { get; set; }

        /// <summary>
        /// Object rotation.
        /// </summary>
        Quaternion Rotation { get; set; }

        /// <summary>
        /// 3D Scale of the object.
        /// </summary>
        Vector3 Scale { get; set; }

        /// <summary>
        /// Loads the object.
        /// </summary>
        void Load(ContentManager content);

        /// <summary>
        /// Updates the physics and input logic.
        /// </summary>
        /// <param name="input">Mouse input. Passed by reference, for the sake of optimisation.</param>
        /// <param name="keyboard">Keyboard input. Passed by reference, for the sake of speed. Microptimisation :TM:</param>
        /// <param name="time">dt. delta-time</param>
        void Update(ref MouseState input,ref KeyboardState keyboard, GameTime time);

        /// <summary>
        /// Draws the game to the ID3D11DeviceContext
        /// </summary>
        /// <param name="time">dt. delta-time</param>
        /// <param name="frustrum">Bounding frustrum for 3D models for GPU optimisation.</param>
        /// <param name="view">View Matrix</param>
        /// <param name="projection">Projection Matrix.</param>
        void Draw(GameTime time,BoundingFrustum frustrum, ref Matrix view, ref Matrix projection);

        /// <summary>
        /// Debug draw. Specific to the game engine editor(s).
        /// </summary>
        /// <param name="time">dt. Delta Time. Except it won't be propably used.</param>
        /// <param name="frustrum">Bounding frustrum allowing a specific drawing optimisation.</param>
        /// <param name="view">View Matrix</param>
        /// <param name="projection">Projection Matrix.</param>
        void EditorDraw(GameTime time, BoundingFrustum frustrum,ref Matrix view,ref Matrix projection);

        /// <summary>
        /// Loads the game object from a file buffer.
        /// </summary>
        /// <param name="buff">file buffer</param>
        /// <param name="position">Buffer position</param>
        /// <param name="result">Loaded IGameObject. Null if failed.</param>
        void LoadF(List<byte> buff,ref int position,out IGameObject result);

        /// <summary>
        /// Saves the game object into a buffer that can be stored in a file.
        /// </summary>
        /// <returns></returns>
        void SaveF(List<byte> buff,ref int position);
    }
}
