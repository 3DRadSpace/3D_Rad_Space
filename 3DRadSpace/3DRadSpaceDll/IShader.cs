using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Base interface for 3D shader effect classes
    /// </summary>
    public interface IShader
    {
        /// <summary>
        /// The class containing the shader itself
        /// </summary>
        Effect Effect { get; set; }
        /// <summary>
        /// A function used internally by the game engine.
        /// </summary>
        void LoadEffect();
        /// <summary>
        /// Draws a model using the specified shader.
        /// </summary>
        /// <param name="mesh"></param>
        /// <param name="world"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        void DrawModel(Model mesh, Matrix world, Matrix view, Matrix projection);
        /// <summary>
        /// Draws a skinmesh with the specified shader.
        /// </summary>
        /// <param name="skinmesh"></param>
        void DrawSkinmesh(Skinmesh skinmesh);
    }
}
