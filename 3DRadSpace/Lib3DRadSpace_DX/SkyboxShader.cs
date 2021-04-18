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
    class SkyboxShader : IShader
    {
        Effect _shader;

        public Effect ShaderEffect
        {
            get
            {
                return _shader;
            }
        }

        public Texture2D SkyboxTexure;

        GraphicsDevice _gdev;

        public void DrawModelPart(ModelMeshPart part, Matrix world, Matrix view, Matrix projection)
        {
            _shader.Parameters["World"].SetValue(world);
            _shader.Parameters["View"].SetValue(view);
            _shader.Parameters["Projection"].SetValue(projection);
            _shader.Parameters["SkyboxTexture"].SetValue(SkyboxTexure);
            _gdev.SetVertexBuffer(part.VertexBuffer);
            _gdev.Indices = part.IndexBuffer;
            foreach(EffectPass pass in _shader.CurrentTechnique.Passes)
            {
                pass.Apply();
                _gdev.DrawIndexedPrimitives(PrimitiveType.TriangleList, part.VertexOffset, part.StartIndex, part.PrimitiveCount);
            }
        }

        public void LoadShader(ContentManager content, GraphicsDevice dev)
        {
            _shader = content.Load<Effect>("Shaders//Skybox");
            _gdev = dev;
        }
    }
}
