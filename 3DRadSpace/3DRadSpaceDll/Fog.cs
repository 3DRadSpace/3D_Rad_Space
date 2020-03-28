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
    /// <para>Fog class. Allows Fog effects on Skinmeshes.</para>
    /// <para>Notice the missing Draw,EditorDraw and Update functions. The fields and properties are only used.</para>
    /// </summary>
    public class Fog : GameObject, IEffectFog
    {
        /// <summary>
        /// Fog class constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="enabled">Is the fog effect allowed?</param>
        /// <param name="color"></param>
        /// <param name="start"></param>
        /// <param name="end"></param>
        public Fog(string name,bool enabled,Color color=default,float start=50,float end=500)
        {
            Name = name;
            Enabled = enabled;
            FogColor = new Vector3(color.R,color.G,color.B);
            FogStart = start;
            FogEnd = end;
        }
        /// <summary>
        /// Empty Fog object constructor.
        /// </summary>
        public Fog()
        {
            Name = "Fog";
            Enabled = false;
            FogColor = new Vector3(255,255,255);
            FogStart = int.MaxValue;
            FogEnd = int.MaxValue;
        }
        /// <summary>
        /// Fog Color. Implemented from IEffectFog.
        /// </summary>
        public Vector3 FogColor
        {
            get
            {
                return _fogcolor;
            }
            set
            {
                if (value.X < 0) value.X = 0;
                if (value.X > 255) value.X = 255;

                if (value.Y < 0) value.Y = 0;
                if (value.Y > 255) value.Y = 255;

                if (value.Z < 0) value.Z = 0;
                if (value.Z > 255) value.Z = 255;
                _fogcolor = value;
            }
        }
        Vector3 _fogcolor;
        /// <summary>
        /// Actually sets this.Enabled. Implemented from IEffectFog.
        /// </summary>
        public bool FogEnabled {
            get { return Enabled; }
            set { Enabled = value; }
        }
        /// <summary>
        /// Fog end distance.
        /// </summary>
        public float FogEnd
        {
            get
            {
                return _fogend;
            }
            set
            {
                if (_fogend < 0) _fogend = 0;
                _fogend = value;
            }
        }
        float _fogend;
        /// <summary>
        /// Fog start distance.
        /// </summary>
        public float FogStart
        {
            get { return _fogstart; }
            set
            {
                if (value < 0) value = 0;
                _fogstart = value;
            }
        }
        float _fogstart;
    }
}
