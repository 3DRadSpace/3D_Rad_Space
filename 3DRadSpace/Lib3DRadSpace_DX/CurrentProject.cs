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
    }
}
