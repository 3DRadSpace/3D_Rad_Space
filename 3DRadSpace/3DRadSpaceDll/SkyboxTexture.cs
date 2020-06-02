using System;
using System.IO;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// A class that contains the textures needed for a skybox object
    /// </summary>
    public class SkyboxTexture : IDisposable
    {
        /// <summary>
        /// Negative X axis texture.
        /// </summary>
        public Texture2D NX;
        /// <summary>
        /// Negative Y axis texture.
        /// </summary>
        public Texture2D NY;
        /// <summary>
        /// Negative Z axis texture.
        /// </summary>
        public Texture2D NZ;

        /// <summary>
        /// Positive X axis texture.
        /// </summary>
        public Texture2D PX;
        /// <summary>
        /// Positive Y axis texture.
        /// </summary>
        public Texture2D PY;
        /// <summary>
        /// Positive Z axis texture.
        /// </summary>
        public Texture2D PZ;

        /// <summary>
        /// Default constructor.
        /// </summary>
        public SkyboxTexture()
        {
            PX = null;
            PY = null;
            PZ = null;
            NX = null;
            NY = null;
            NZ = null;
        }
        /// <summary>
        /// Generates a SkyboxTexture from a array of textures.
        /// </summary>
        /// <param name="textures"></param>
        public SkyboxTexture(Texture2D[] textures)
        {
            PX = textures[0];
            PY = textures[1];
            PZ = textures[2];
            NX = textures[3];
            NY = textures[4];
            NZ = textures[5];
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="gd"></param>
        /// <param name="files"></param>
        public void LoadFromGivenFiles(GraphicsDevice gd,string[] files)
        {
            FileStream px_str = new FileStream(files[0], FileMode.Open);
            FileStream py_str = new FileStream(files[1], FileMode.Open);
            FileStream pz_str = new FileStream(files[2], FileMode.Open);
            FileStream nx_str = new FileStream(files[3], FileMode.Open);
            FileStream ny_str = new FileStream(files[4], FileMode.Open);
            FileStream nz_str = new FileStream(files[5], FileMode.Open);

            NX = Texture2D.FromStream(gd, px_str);
            NY = Texture2D.FromStream(gd, py_str);
            NZ = Texture2D.FromStream(gd, pz_str);
            PX = Texture2D.FromStream(gd, nx_str);
            PY = Texture2D.FromStream(gd, ny_str);
            PZ = Texture2D.FromStream(gd, nz_str);

            px_str.Dispose();
            py_str.Dispose();
            pz_str.Dispose();
            nx_str.Dispose();
            ny_str.Dispose();
            nz_str.Dispose();
        }

        /// <summary>
        /// Generates a skybox object using the default constructor.
        /// </summary>
        /// <returns></returns>
        public Skybox GenerateSkybox()
        {
            Skybox r = new Skybox();
            r.Texture.PX = PX;
            r.Texture.PX = PY;
            r.Texture.PX = PZ;
            r.Texture.NX = NX;
            r.Texture.NY = NY;
            r.Texture.NZ = NZ;
            return r;
        }
        /// <summary>
        /// Returns an array containing the textures.
        /// </summary>
        /// <returns></returns>
        public Texture2D[] GenerateArray()
        {
            Texture2D[] a = new Texture2D[6];
            a[0] = PX;
            a[1] = PY;
            a[2] = PZ;
            a[3] = NZ;
            a[4] = NY;
            a[5] = NZ;
            return a;
        }

        bool _disposed;
        /// <summary>
        /// Frees the textures from memory.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        void Dispose(bool disposing)
        {
            if (_disposed == true) return;
            if(disposing)
            {
                NX.Dispose();
                NY.Dispose();
                NZ.Dispose();
                PX.Dispose();
                PY.Dispose();
                PZ.Dispose();
                _disposed = true;
            }
        }
    }
}
