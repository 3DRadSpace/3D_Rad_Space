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
            FogEnabled = enabled;
            FogStart = start;
            FogEnd = end;
        }
        /// <summary>
        /// Fog Color.
        /// </summary>
        public Vector3 FogColor { get; set; }
        /// <summary>
        /// Property from IEffectFog. this.Enabled has always the same value.
        /// </summary>
        public bool FogEnabled
        {
            get
            {
                return FogEnabled;
            }
            set
            {
                Enabled = value;
            }
        }
        /// <summary>
        /// Fog end distance.
        /// </summary>
        public float FogEnd { get; set; }
        /// <summary>
        /// Fog start distance.
        /// </summary>
        public float FogStart { get; set; }

        /// <summary>
        /// Override of the GameObject.Enable to allow the usage of FogEnabled.
        /// </summary>
        public new bool Enabled
        {
            get
            {
                return FogEnabled;
            }
            set
            {
                FogEnabled = value;
            }
        }
    }
}
