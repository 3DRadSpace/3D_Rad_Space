using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

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
        public static List<BaseGameObject> GameObjects = new List<BaseGameObject>(300);

        /// <summary>
        /// Opens a project, resetting the gameobject's content.
        /// </summary>
        /// <param name="filename"></param>
        public static void Open(string filename)
        {
            GameObjects.Clear();
            Add(filename);
        }
        static BaseGameObject ReadObject(byte[] buffer, ref int position)
        {
            IGameObject result = null;
            byte id = buffer[position];
            position++;
            switch((GameObjectType)id)
            {
                case GameObjectType.Empty:
                {
                    EmptyGameObject e = new EmptyGameObject();
                    e.LoadF(buffer, ref position, out result);
                    break;
                }
            }
            return (BaseGameObject)result;
        }
        /// <summary>
        /// Opens a project, concatenating the current project with the opened project.
        /// </summary>
        /// <param name="filename"></param>
        public static void Add(string filename)
        {
            byte[] filebuffer = File.ReadAllBytes(filename);
            for(int i = 0; i < filebuffer.Length; i++)
            {
                BaseGameObject obj = ReadObject(filebuffer, ref i);
                GameObjects.Add(obj);
            }
        }
        /// <summary>
        /// Saves the current project into a file.
        /// </summary>
        /// <param name="filename"></param>
        public static void Save(string filename)
        {
            List<byte> buffer = new List<byte>(1024 * 10); //allocate 10 KBs xd
            for(int i = 0; i < GameObjects.Count; i++)
            {
                GameObjects[i].SaveF(buffer);
            }
            File.WriteAllBytes(filename, buffer.ToArray());
        }
        /// <summary>
        /// 
        /// </summary>
        public static Vector2 Resolution;

        /// <summary>
        /// Contains a reference to the current ID3D11GraphicsDevice + ID3D11DeviceContext.
        /// </summary>
        public static GraphicsDevice GraphicsDevice;

        /// <summary>
        /// 
        /// </summary>
        public static Shaders.SkyboxShader SkyboxShader { get; } = new Shaders.SkyboxShader();

        /// <summary>
        /// 
        /// </summary>
        public static Shaders.BasicColorShader BasicColorShader { get; } = new Shaders.BasicColorShader();

        /// <summary>
        /// 
        /// </summary>
        public static Shaders.TexturedMeshShader TexturedMeshShader { get; } =  new Shaders.TexturedMeshShader();
        
        /// <summary>
        /// Returns the first object that matches the exact name specified.
        /// Returns null if there isn't any object that has the exact Name as the specified parameter.
        /// </summary>
        /// <param name="filename">Specified name.</param>
        public static BaseGameObject FindObjectByName(string name)
        {
            for(int i =0 ; i < GameObjects.Count; i++)
            {
                if(GameObjects[i].Name == name) return GameObjects[i];
            }
            return null;
        }
        /// <summary>
        /// Returns a collection of objects that share the the specified name.
        /// Notice: Use the FindObjectsByName(string name,int capacity) for a more GC-friendly approach.
        /// </summary>
        /// <param name="filename">Specified name.</param>
        public static BaseGameObject[] FindObjectsByName(string name)
        {
            List<BaseGameObject> _r = new List<BaseGameObject>(20);
            for(int i =0 ; i < GameObjects.Count; i++)
            {
                if(GameObjects[i].Name == name) _r.Add(GameObjects[i]);
            }
            return _r.ToArray();
        }
        /// <summary>
        /// Returns a collection of objects that share the the specified name.
        /// Notice: Use the FindObjectsByName(string name,int capacity) for a more GC-friendly approach.
        /// </summary>
        /// <param name="filename">Specified name.</param>
        /// <param name="capacity">Number of objects that are going potentially going to be returned.</param>
        public static BaseGameObject[] FindObjectsByName(string name,int capacity)
        {
            BaseGameObject[] r = new BaseGameObject[capacity];
            int j =0;
            for(int i =0 ; i < GameObjects.Count;i++)
            {
                if(GameObjects[i].Name == name)
                {
                    r[j] = GameObjects[i];
                    j++;
                }
                if(j == capacity-1) break;
            }
            return r;
        }
        /// <summary>
        /// Returns the object with the specified ID.
        /// This is a shorter way of writing CurrentProject.GameObjects[id];
        /// Notice: This doesn't check the bounds of the object list.
        /// </summary>
        /// <param name="filename">Specified identifier.</param>
        public static BaseGameObject FindObjectByID(int id)
        {
            return GameObjects[id];
        }
    }
}
