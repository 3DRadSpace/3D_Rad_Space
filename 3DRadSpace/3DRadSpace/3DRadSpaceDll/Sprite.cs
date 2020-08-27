using Assimp.Configs;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    class Sprite : GameObject
    {
        public Texture2D Texture;
        public new float Rotation;
        public Sprite(string name,bool enabled,Vector2 pos,Vector2 scale,Vector2 pivot,float angle,float layer)
        {
            Name = name;
            Enabled = enabled;
            Position = new Vector3(pos, layer);
            Rotation = angle;

        }
    }
}
