using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace Lib3DRadSpace_DX
{
    namespace Shaders
    {
        /// <summary>
        /// Represents the base type for Skinmesh shaders.
        /// </summary>
        public interface IShader
        {
            /// <summary>
            /// Loads the shader's code.
            /// </summary>
            /// <param name="content">Content pipeline</param>
            /// <param name="dev">ID3D11Device used to initialize the shader effects</param>
            void LoadShader(ContentManager content,GraphicsDevice dev);
            /// <summary>
            /// Draw a shaded mesh
            /// </summary>
            /// <param name="part">Mesh to be drawn</param>
            /// <param name="world">World matrix</param>
            /// <param name="view">View matrix</param>
            /// <param name="projection">Projection matrix</param>
            void DrawModelPart(ModelMeshPart part,Matrix world, Matrix view, Matrix projection);
            /// <summary>
            /// Gets the shader.
            /// </summary>
            Effect ShaderEffect { get; }
        }
    }
}
