using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Representsa Fog effect that can be used on Skinmesh objects.
    /// </summary>
    public class Fog : BaseGameObject
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="visible"></param>
        /// <param name="fogcolor"></param>
        /// <param name="fogstart"></param>
        /// <param name="fogend"></param>
        public Fog(string name="Fog",bool visible=true,Color fogcolor=default,float fogstart=100f,float fogend=200f)
        {
            Name = name;
            Visible = visible;
            FogColor = fogcolor;
            FogStart = fogstart;
            FogEnd = fogend;
        }
        /// <summary>
        /// Describes the fog colour in a RGB format.
        /// </summary>
        public Color FogColor;
        /// <summary>
        /// Represents the fog gradient start distance.
        /// </summary>
        public float FogStart;
        /// <summary>
        /// Represents the fog gradient end distance.
        /// </summary>
        public float FogEnd;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        /// <param name="position"></param>
        /// <param name="result"></param>
        public override void LoadF(byte[] buff, ref int position, out IGameObject result)
        {
            string name = ByteCodeParser.GetString(buff, ref position);
            bool visible = ByteCodeParser.GetBool(buff, ref position);
            Color color = ByteCodeParser.GetColor(buff,ref position);
            Vector2 v1 = ByteCodeParser.GetVector2(buff, ref position);
            result = new Fog(name, visible, color, v1.X, v1.Y);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        public override void SaveF(List<byte> buff)
        {
            ByteCodeParser.SetString(buff, Name);
            ByteCodeParser.SetBool(buff, Visible);
            ByteCodeParser.SetColor(buff, FogColor);
            ByteCodeParser.SetVector2(buff, new Vector2(FogStart, FogEnd));
        }
    }
}
