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
    public class SkyboxShader : IShader
    {
        Effect _shader;

        /// <summary>
        /// 
        /// </summary>
        public Effect ShaderEffect
        {
            get
            {
                return _shader;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public Texture2D SkyboxTexure;

        /// <summary>
        /// 
        /// </summary>
        public float FlipOffsetX = 0.0f;

        /// <summary>
        /// 
        /// </summary>
        public float FlipOffsetY = 0.0f;

        GraphicsDevice _gdev;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="part"></param>
        /// <param name="world"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public void DrawModelPart(ModelMeshPart part, Matrix world, Matrix view, Matrix projection)
        {
            _shader.Parameters["World"].SetValue(world);
            _shader.Parameters["View"].SetValue(view);
            _shader.Parameters["Projection"].SetValue(projection);
            _shader.Parameters["SkyboxTexture"].SetValue(SkyboxTexure);
            _shader.Parameters["UVOffsetX"].SetValue(FlipOffsetX);
            _shader.Parameters["UVOffsetY"].SetValue(FlipOffsetY);
            _gdev.SetVertexBuffer(part.VertexBuffer);
            _gdev.Indices = part.IndexBuffer;
            foreach(EffectPass pass in _shader.CurrentTechnique.Passes)
            {
                pass.Apply();
                _gdev.DrawIndexedPrimitives(PrimitiveType.TriangleList, part.VertexOffset, part.StartIndex, part.PrimitiveCount);
            }
        }

        /// <summary>
        /// B
        /// </summary>
        /// <param name="content"></param>
        /// <param name="dev"></param>
        public void LoadShader(ContentManager content, GraphicsDevice dev)
        {
            _shader = content.Load<Effect>("Shaders//Skybox");
            _gdev = dev;
        }
    }
}
