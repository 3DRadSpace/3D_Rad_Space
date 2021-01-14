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
            public static Effect MainEffect;
            /// <summary>
            /// 
            /// </summary>
            public Effect ShaderEffect
            {
                get
                {
                    return MainEffect.Clone();
                }
            }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="effect"></param>
            /// <param name="part"></param>
            /// <param name="world"></param>
            /// <param name="view"></param>
            /// <param name="projection"></param>
            public void DrawModelPart(Effect effect, ModelMeshPart part, Matrix world, Matrix view, Matrix projection)
            {
                if (part.PrimitiveCount > 0)
                {
                    effect.Parameters["MColor"].SetValue(ModelColor.ToVector4());
                    effect.Parameters["World"].SetValue(world);
                    effect.Parameters["View"].SetValue(view);
                    effect.Parameters["Projection"].SetValue(projection);
                    foreach (EffectPass pass in effect.CurrentTechnique.Passes)
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
                MainEffect = content.Load<Effect>("Shaders\\BasicColorShader");
            }
            GraphicsDevice _dev;
        }
    }
}
