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
    class VertexColorShader : IShader
    {
        public Color VertexColor
        {
            get
            {
                return new Color(vColorParam.X * 255, vColorParam.Y * 255, vColorParam.Z * 255, vColorParam.W * 255);
            }
            set
            {
                vColorParam = value.ToVector4();
            }
        }
        Vector4 vColorParam;

        public Effect _shader;

        GraphicsDevice _gdev;

        public Effect ShaderEffect => _shader;

        public void DrawModelPart(Effect effect, ModelMeshPart part, Matrix world, Matrix view, Matrix projection)
        {
            _shader.Parameters["VertexColor"].SetValue(vColorParam);
            _shader.Parameters["World"].SetValue(world);
            _shader.Parameters["View"].SetValue(view);
            _shader.Parameters["Projection"].SetValue(projection);
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
            _shader = content.Load<Effect>("Shaders//VertexColor");
            _gdev = dev;
        }
    }
}
