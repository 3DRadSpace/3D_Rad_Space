using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using System.IO;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Represents an Skybox object.
    /// </summary>
    public class Skybox : GameObject,IDisposable
    {
        /// <summary>
        /// Empty constructor.
        /// </summary>
        public Skybox()
        {
            _size = 400f;
            Name = "Skybox";
            Enabled = false;
        }
        /// <summary>
        /// Main skybox constructor.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="path"></param>
        public Skybox(string name,bool enabled,string path)
        {
            Name = name;
            Enabled = enabled;
            Resource = path;
        }
        /// <summary>
        /// Size of the cube itself.
        /// </summary>
        public float Size
        {
            get
            {
                return _size;
            }
            set
            {
                _size = value;
                if (Size <= 0) throw new ArgumentException("Size cannot be smaller than or equal to 0.");
            }
        }
        /// <summary>
        /// Loads the skybox.
        /// </summary>
        /// <param name="content"></param>
        /// <param name="gd">GraphicsDevice used to initialize the texture.</param>
        public void Load(ContentManager content, GraphicsDevice gd)
        {
            _skyBoxCube = content.Load<Model>("Skybox\\Skybox");

            string[] textures_list = File.ReadAllLines(Resource);
            Texture.LoadFromGivenFiles(gd,textures_list);

            epx = new BasicEffect(gd)
            {
                DiffuseColor = new Vector3(1, 1, 1),
                TextureEnabled = true,
                Texture = Texture.PX,
            };
            epy = new BasicEffect(gd)
            {
                DiffuseColor = new Vector3(1, 1, 1),
                TextureEnabled = true,
                Texture = Texture.PY,
            };
            epz = new BasicEffect(gd)
            {
                DiffuseColor = new Vector3(1, 1, 1),
                TextureEnabled = true,
                Texture = Texture.PZ,
            };
            enx = new BasicEffect(gd)
            {
                DiffuseColor = new Vector3(1, 1, 1),
                TextureEnabled = true,
                Texture = Texture.NX,
            };
            eny = new BasicEffect(gd)
            {
                DiffuseColor = new Vector3(1, 1, 1),
                TextureEnabled = true,
                Texture = Texture.NY,
            };
            enz = new BasicEffect(gd)
            {
                DiffuseColor = new Vector3(1, 1, 1),
                TextureEnabled = true,
                Texture = Texture.NZ,
            };

            LinkAvalableCamera();

            base.Load(content);
        }
        float _size;
        Camera _linkedc;
        Model _skyBoxCube;
        BasicEffect epx, epy, epz, enx, eny, enz;
        /// <summary>
        /// A entire image representing the skybox.
        /// </summary>
        public SkyboxTexture Texture;
        /// <summary>
        /// Draws the skybox.
        /// </summary>
        /// <param name="spriteBatch"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (_linkedc == null) LinkAvalableCamera(); //We determine a avalable Camera object 

            Matrix transformation = Matrix.CreateTranslation(_linkedc.Position);

            base.Draw(spriteBatch, view, projection);
        }

        /// <summary>
        /// Draws the skybox in the editor - an extra argument is needed.
        /// </summary>
        /// <param name="editor_cam_pos"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public void EditorDraw(Vector3 editor_cam_pos, Matrix view, Matrix projection)
        {
            //TODO: insert drawing code, oh God, this is going to be painfull
            base.EditorDraw(null, null, null);
        }
        /// <summary>
        /// Finds a camera object to link the skybox to.
        /// </summary>
        public void LinkAvalableCamera()
        {
            for (int i = 0; i < Game.GameObjects.Count; i++)
            {
                if (Game.GameObjects[i] is Camera c)
                {
                    if (c.Enabled)
                    {
                        _size = c.MaxDrawDist - 1;
                        _linkedc = c;
                        Position = c.Position;
                    }
                }
            }
        }
        /// <summary>
        /// Frees the loaded texture.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        bool _disposed = false;
        /// <summary>
        /// Protected Dispose().
        /// </summary>
        /// <param name="disposing"></param>
        protected void Dispose(bool disposing)
        {
            if (_disposed) return;
            if (disposing)
            {
                Texture.Dispose();
            }
            _disposed = true;
        }
    }
}
