using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using System.IO;
using Microsoft.Xna.Framework.Audio;

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
        /// 
        /// SKYBOX FILE FORMAT:
        /// EXTENSION: .sky
        /// 
        /// First line: PX image
        /// Second line: PY image
        /// Third line: PZ image
        /// Fourth line: NX image
        /// Fifth line: NY image
        /// Sixth line: NZ image
        /// 
        /// </summary>
        /// <param name="content"></param>
        /// <param name="gd">GraphicsDevice used to initialize the texture.</param>
        public void Load(ContentManager content, GraphicsDevice gd)
        {
            _skyBoxCube = content.Load<Model>("Skybox\\Skybox");

            string[] textures_list = File.ReadAllLines(Resource);

            /*
             * MARKING BEGINNING OF HORRIBLE CODE
             */ 

            //My motivation loss is really a bitch.

            BasicEffect _px, _py, _pz, _nx, _ny, _nz; //NOTE: Names are misleding, or not?
            _px = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[2].Effect);
            _py = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[0].Effect);
            _pz = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[3].Effect);
            _nx = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[4].Effect);
            _ny = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[5].Effect);
            _nz = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[1].Effect);
            //haha bad code, this is me, the next yandere dev
            
            //Since the texture order is wrong, there is a total of 6! total combinations. *begins to smash keyboad*
            //Also, count the fact that the textures images may need to be flipped. So that's a total of 4*(6!) total skybox textures combinations. Guess I'm f*'d.

            _setEffectTexture(gd, _px, Path.GetDirectoryName(Resource) + "//" + textures_list[0]);
            _setEffectTexture(gd, _py, Path.GetDirectoryName(Resource) + "//" + textures_list[1]);
            _setEffectTexture(gd, _pz, Path.GetDirectoryName(Resource) + "//" + textures_list[2]);
            _setEffectTexture(gd, _nx, Path.GetDirectoryName(Resource) + "//" + textures_list[3]);
            _setEffectTexture(gd, _ny, Path.GetDirectoryName(Resource) + "//" + textures_list[4]);
            _setEffectTexture(gd, _nz, Path.GetDirectoryName(Resource) + "//" + textures_list[5]);
            //where defok is the for() statement reeee

            /*
             * MARKING END OF HORRIBLE CODE
             */
            LinkAvalableCamera();
            base.Load(content);
        }
        void _setEffectTexture(GraphicsDevice gd ,BasicEffect ef,string texture)
        {
            ef.TextureEnabled = true;
            FileStream str = new FileStream(texture, FileMode.Open);
            ef.Texture = Texture2D.FromStream(gd, str);
            str.Dispose();
        }
        float _size;
        Camera _linkedc;
        Model _skyBoxCube;
        /// <summary>
        /// A entire image representing the skybox.
        /// </summary>
        public Texture2D PX,PY,PZ,NX,NY,NZ;
        /// <summary>
        /// Draws the skybox.
        /// </summary>
        /// <param name="spriteBatch"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (_linkedc == null) LinkAvalableCamera(); //We determine a avalable Camera object 

            Matrix t = Matrix.CreateScale(_size) * Matrix.CreateTranslation(_linkedc.Position);
            foreach(ModelMesh mesh in _skyBoxCube.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.View = view.Value;
                    effect.Projection = projection.Value;
                    effect.World = t;
                    effect.DiffuseColor = Vector3.One;
                }
                mesh.Draw();
            }

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
            Matrix t = Matrix.CreateScale(_size) * Matrix.CreateTranslation(editor_cam_pos);
            foreach (ModelMesh mesh in _skyBoxCube.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.View = view;
                    effect.Projection = projection;
                    effect.World = t;
                    effect.DiffuseColor = Vector3.One;
                }
                mesh.Draw();
            }
            base.EditorDraw(null, null, null);
        }
        /// <summary>
        /// Finds a camera object to link the skybox to.
        /// </summary>
        public void LinkAvalableCamera()
        {
            for (int i = 0; i < Main.GameObjects.Count; i++)
            {
                if (Main.GameObjects[i] is Camera c) LinkCamera(c);
            }
        }
        /// <summary>
        /// Links a camera to the object
        /// </summary>
        /// <param name="c"></param>
        public void LinkCamera(Camera c)
        {
            if (c.Enabled)
            {
                _size = c.MaxDrawDist - 1;
                _linkedc = c;
                Position = c.Position;
            }
        }
        /// <summary>
        /// Updates the skyboxes size in case that the linked camera's maximum drawing distance also changed.
        /// </summary>
        public void UpdateSize()
        {
            _size = _linkedc.MaxDrawDist - 1;
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
                NX?.Dispose();
                NY?.Dispose();
                NZ?.Dispose();
                PX?.Dispose();
                PY?.Dispose();
                PZ?.Dispose();
            }
            _disposed = true;
        }
    }
}
