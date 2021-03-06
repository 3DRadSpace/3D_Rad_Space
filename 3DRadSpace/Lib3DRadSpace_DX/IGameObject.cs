﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Absolute base interface for all of the "game-objects" in 3DRadSpace.
    /// Specific objects will have their own specific function overloading for the Update()/Draw() functions
    /// </summary>
    public interface IGameObject
    {
        /// <summary>
        /// Loads the object.
        /// </summary>
        void Load(ContentManager content);

        /// <summary>
        /// Adds the object to the physics updateables list. Internal use only.
        /// </summary>
        /// <param name="space"></param>
        void PhysicsInitialize(BEPUphysics.Space space);

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
        /// <param name="frustrum">Bounding frustrum for 3D models for a culling optimisation.</param>
        /// <param name="view">View Matrix</param>
        /// <param name="projection">Projection Matrix.</param>
        void Draw(GameTime time,BoundingFrustum frustrum, ref Matrix view, ref Matrix projection);

        /// <summary>
        /// Draws 2D elements into the sprite batch.
        /// </summary>
        /// <param name="time">dt</param>
        /// <param name="batch">SpriteBatch</param>
        void Draw2D(GameTime time, SpriteBatch batch);

        /// <summary>
        /// Debug draw. Specific to the game engine editor(s).
        /// </summary>
        /// <param name="time">dt. Delta Time. Except it won't be propably used.</param>
        /// <param name="frustrum">Bounding frustrum allowing a specific drawing optimisation.</param>
        /// <param name="view">View Matrix</param>
        /// <param name="projection">Projection Matrix.</param>
        void EditorDraw(GameTime time, BoundingFrustum frustrum,ref Matrix view,ref Matrix projection);

        /// <summary>
        /// Used in the editor. Can also be used when ray tracing objects.
        /// </summary>
        /// <param name="ray"></param>
        /// <returns></returns>
        Vector3? RayIntersection(Ray ray);

        /// <summary>
        /// Loads the game object from a file buffer.
        /// </summary>
        /// <param name="buff">file buffer</param>
        /// <param name="position">Buffer position</param>
        /// <param name="result">Loaded IGameObject. Null if failed.</param>
        void LoadF(byte[] buff,ref int position,out IGameObject result);

        /// <summary>
        /// Saves the game object into a buffer that can be stored in a file.
        /// </summary>
        /// <returns></returns>
        void SaveF(List<byte> buff);

        /// <summary>
        /// Unloads native resources when loading an other project.
        /// </summary>
        void Unload();
    }
}
