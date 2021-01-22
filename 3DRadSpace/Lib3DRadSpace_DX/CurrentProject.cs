using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

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
            byte[] filebuffer = File.ReadAllBytes(filename);
            for(int i =0; i < filebuffer.Length;i++)
            {
                ReadObject(filebuffer, i);
                i++;
                switch(true)
                {
                    default: break;
                }
            }
        }
        static void ReadObject(byte[] buffer,int position)
        {
            //3DRadSpace would allow by this implementation a maximum of 255 objects XD
            switch(buffer[position])
            {
                default: break;
            }
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
            List<byte> buffer = new List<byte>(1024*10); //allocate ~10 initial KBs lol
            for(int i =0; i< GameObjects.Count;i++)
            {
                GameObjects[i].SaveF(buffer, ref i);
            }
        }
    }
}
