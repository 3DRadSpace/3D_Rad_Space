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
        public static void DrawModel(Model model,Matrix world,Matrix view,Matrix projection)
        {
            foreach(ModelMesh mesh in model.Meshes)
            {
                foreach(BasicEffect effect in mesh.Effects)
                {
                    effect.World = world;
                    effect.View = view;
                    effect.Projection = projection;
                    effect.EnableDefaultLighting();
                }
                mesh.Draw();
            }
        }
    }
}
