using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Contains methods and fields for managing game objects.
    /// </summary>
    public static class Game
    {
        /// <summary>
        /// Contains the objects. 
        /// </summary>
        public static List<object> GameObjects;
        /// <summary>
        /// Draws a 3D Model.
        /// </summary>
        /// <param name="model">3D Model</param>
        /// <param name="world">Scale*Rotaion*Position Matrix</param>
        /// <param name="view">View matrix</param>
        /// <param name="projection">Projection Matrix</param>
        /// <param name="FogEnabled">Allows Fog effects on the model</param>
        /// <param name="FogColor">Fog colour if allowed</param>
        /// <param name="FogStart">Fog Start Distance</param>
        /// <param name="FogEnd">Fog End Distance</param>
        public static void DrawModel(Model model,Matrix world,Matrix view,Matrix projection,bool FogEnabled = false,Vector3 FogColor = default,float FogStart=0,float FogEnd=0)
        {
            foreach(ModelMesh mesh in model.Meshes)
            {
                foreach(BasicEffect effect in mesh.Effects)
                {
                    effect.World = world;
                    effect.View = view;
                    effect.Projection = projection;
                    effect.FogEnabled = FogEnabled;
                    effect.FogColor = FogColor;
                    effect.FogStart = FogStart;
                    effect.FogEnd = FogEnd;
                }
                mesh.Draw();
            }
        }
        /// <summary>
        /// Finds an objects after it's id.
        /// </summary>
        /// <param name="i">Numeric indentifier.</param>
        /// <returns>Returns the found object.</returns>
        public static object FindObject(int i)
        {
            if (i < 0) return null;
            if (i > GameObjects.Count) return null;
            return GameObjects[i];
        }
        /// <summary>
        /// Sets an object in the list.
        /// </summary>
        /// <param name="i">Object unique numeric IDentifier / array index</param>
        /// <param name="obj">Value</param>
        public static void SetObject(int i,object obj)
        {
            if (i < 0) return;
            if (i > GameObjects.Count) return;
            GameObjects[i] = obj;
        }
    }
}
