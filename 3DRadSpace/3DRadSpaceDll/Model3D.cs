/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assimp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.IO;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Represents a skinmesh model.
    /// </summary>
    public class Model3D : IDisposable
    {
        /// <summary>
        /// Empty constructor,
        /// </summary>
        public Model3D(GraphicsDevice gd)
        {
            Matrix = Matrix.Identity;
            Shaders = new List<Effect>();
            GraphicsDevice = gd;
        }
        /// <summary>
        /// 
        /// </summary>
        public GraphicsDevice GraphicsDevice {get; private set;}

        /// <summary>
        /// Matrix used to transform the entire model.
        /// </summary>
        public Matrix Matrix;

        /// <summary>
        /// Generates a scale/rotation/translation matrix.
        /// </summary>
        /// <returns></returns>
        public Matrix GenerateSRT(Vector3 position,Vector3 eulerangles,Vector3 scale)
        {
            return Matrix.CreateScale(scale) * Matrix.CreateFromYawPitchRoll(eulerangles.Y,eulerangles.X,eulerangles.Z) * Matrix.CreateTranslation(scale);
        }

        /// <summary>
        /// List of shaders. One shader per texture.
        /// </summary>
        public List<Effect> Shaders;

        /// <summary>
        /// List of meshes
        /// </summary>
        public List<Mesh3D> Meshes { get; private set; }

        /// <summary>
        /// Gets the number of textures.
        /// </summary>
        public int TextureCount { get; private set; }

        /// <summary>
        /// Gets the number of textures.
        /// </summary>
        public int MeshCount { get; private set; }

        Matrix MatrixToXNA(Matrix4x4 matrix)
        {
            Matrix r = new Matrix();
            r.M11 = matrix.A1;
            r.M12 = matrix.A2;
            r.M13 = matrix.A3;
            r.M14 = matrix.A4;

            r.M21 = matrix.B1;
            r.M22 = matrix.B2;
            r.M23 = matrix.B3;
            r.M24 = matrix.B4;

            r.M31 = matrix.C1;
            r.M32 = matrix.C2;
            r.M33 = matrix.C3;
            r.M34 = matrix.C4;

            r.M41 = matrix.D1;
            r.M42 = matrix.D2;
            r.M43 = matrix.D3;
            r.M44 = matrix.D4;
            return r;
        }
        Color ColorToXNA(Color3D color)
        {
            return new Color(color.R, color.G, color.B);
        }
        Color ColorToXNA(Color4D color)
        {
            return new Color(color.R, color.G, color.B, color.A);
        }
        /// <summary>
        /// Loads a mesh from the specified path.
        /// </summary>
        /// <param name="path"></param>
        public void Load(string path)
        {
            AssimpContext context = new AssimpContext();
            Scene scene = context.ImportFile(path);
            if(!scene.HasMeshes)
            {
                context.Dispose();
                return;
            }
            if(scene.HasTextures)
            {
                TextureCount = scene.TextureCount;
                for(int i =0; i < scene.TextureCount;i++)
                {
                    Mesh3D m = new Mesh3D();
                    if (!scene.Textures[i].IsCompressed)
                    {
                        m.texture = new Texture2D(GraphicsDevice, scene.Textures[i].Width, scene.Textures[i].Height);
                        Color[] c = new Color[scene.Textures[i].NonCompressedData.Length];
                        for(int j =0; j < 0; j++)
                        {
                            c[j] = new Color(scene.Textures[i].NonCompressedData[i].R, scene.Textures[i].NonCompressedData[i].G, scene.Textures[i].NonCompressedData[i].B);
                        }
                        m.texture.SetData(c);
                    }
                }
            }
            if(scene.HasMaterials)
            {
                scene.Materials[0].
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        /// <param name="world"></param>
        public void Draw(Matrix view,Matrix projection,Matrix world)
        {
            
        }
        /// <summary>
        /// Unloads unmanaged resources (textures, in this case)
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        void Dispose(bool disposing)
        {
            if (_disposed) return;
            if(disposing)
            {
                //Dispose all textures.
                for(int i =0; i < TextureCount;i++)
                {
                    Meshes[i].texture?.Dispose();
                }
            }
        }
        bool _disposed;
    }
}
*/