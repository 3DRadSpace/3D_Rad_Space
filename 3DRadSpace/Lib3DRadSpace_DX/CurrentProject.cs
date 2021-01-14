using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Contains settings and the objects that are in the currently loaded project.
    /// </summary>
    public static class CurrentProject
    {
        /// <summary>
        /// A list containing the game objects.
        /// </summary>
        public static List<BaseGameObject> GameObjects;

        /// <summary>
        /// Opens a project, resetting the gameobject's content.
        /// </summary>
        /// <param name="filename"></param>
        public static void Open(string filename)
        {
            GameObjects.Clear();
        }
        /// <summary>
        /// Opens a project, concatenating the current project with the opened project.
        /// </summary>
        /// <param name="filename"></param>
        public static void Add(string filename)
        {
            
        }
        /// <summary>
        /// Saves the current project into a file.
        /// </summary>
        /// <param name="filename"></param>
        public static void Save(string filename)
        {

        }
    }
}
