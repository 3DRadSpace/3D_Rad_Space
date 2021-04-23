using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    namespace Shaders
    {
        /// <summary>
        /// 
        /// </summary>
        public class BasicColorShader : IShader
        {
            /// <summary>
            /// 
            /// </summary>
            public Color ModelColor;
            /// <summary>
            /// 
            /// </summary>
            Effect _eff;
            /// <summary>
            /// 
            /// </summary>
            public Effect ShaderEffect
            {
                get
                {
                    return _eff;
                }
            }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="part"></param>
            /// <param name="world"></param>
            /// <param name="view"></param>
            /// <param name="projection"></param>
            public void DrawModelPart(ModelMeshPart part, Matrix world, Matrix view, Matrix projection)
            {
                if (part.PrimitiveCount > 0)
                {
                    _eff.Parameters["PlainColor"].SetValue(ModelColor.ToVector4());
                    _eff.Parameters["World"].SetValue(world);
                    _eff.Parameters["View"].SetValue(view);
                    _eff.Parameters["Projection"].SetValue(projection);
                    foreach (EffectPass pass in _eff.CurrentTechnique.Passes)
                    {
                        pass.Apply();
                        _dev.Indices = part.IndexBuffer;
                        _dev.SetVertexBuffer(part.VertexBuffer);
                        _dev.DrawIndexedPrimitives(PrimitiveType.TriangleList, part.VertexOffset, part.StartIndex, part.PrimitiveCount);
                    }
                }
            }

            /// <summary>
            /// Internal use.
            /// </summary>
            /// <param name="content"></param>
            /// <param name="dev"></param>
            public void LoadShader(ContentManager content, GraphicsDevice dev)
            {
                _dev = dev;
                _eff = content.Load<Effect>("Shaders\\BasicColor");
            }
            GraphicsDevice _dev;
        }
    }
}
