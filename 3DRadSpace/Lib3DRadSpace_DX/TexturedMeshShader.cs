using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX.Shaders
{
    /// <summary>
    /// 
    /// </summary>
    public class TexturedMeshShader : IShader
    {
        /// <summary>
        /// Gets the effect itself.
        /// </summary>
        public Effect ShaderEffect
        {
            get
            {
                return _effect;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public Texture Texture;

        /// <summary>
        /// Draws a model part with a specified texture.
        /// </summary>
        /// <param name="part"></param>
        /// <param name="world"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public void DrawModelPart(ModelMeshPart part, Matrix world, Matrix view, Matrix projection)
        {
            _effect.Parameters["World"].SetValue(world);
            _effect.Parameters["View"].SetValue(view);
            _effect.Parameters["Projection"].SetValue(projection);
            _effect.Parameters["SkyboxTexture"].SetValue(Texture);
            gd.SetVertexBuffer(part.VertexBuffer);
            gd.Indices = part.IndexBuffer;
            foreach(EffectPass pass in _effect.CurrentTechnique.Passes)
            {
                pass.Apply();
                gd.DrawIndexedPrimitives(PrimitiveType.TriangleList, part.VertexOffset, part.StartIndex, part.PrimitiveCount);
            }
        }

        GraphicsDevice gd;
        Effect _effect;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="content"></param>
        /// <param name="dev"></param>
        public void LoadShader(ContentManager content, GraphicsDevice dev)
        {
            _effect = content.Load<Effect>("Shaders\\TexturedMesh");
            gd = dev;
        }
    }
}
