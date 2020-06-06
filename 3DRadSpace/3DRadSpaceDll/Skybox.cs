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
        /// First line: Skybox name
        /// Second line: PX image
        /// Second line: PY image
        /// Second line: PZ image
        /// Second line: NX image
        /// Second line: NY image
        /// Second line: NZ image
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

            BasicEffect _px, _py, _pz, _nx, _ny, _nz;
            _px = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[0].Effect);
            _py = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[1].Effect);
            _pz = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[2].Effect);
            _nx = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[3].Effect);
            _ny = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[4].Effect);
            _nz = ((BasicEffect)_skyBoxCube.Meshes[0].MeshParts[5].Effect);
            //haha bad code, this is me, the next yandere dev
            _setEffectTexture(gd,_px,"Content//"+ textures_list[0]+"//"+ textures_list[1]);
            _setEffectTexture(gd,_py,"Content//"+ textures_list[0]+"//"+ textures_list[2]);
            _setEffectTexture(gd,_pz,"Content//"+ textures_list[0]+"//"+ textures_list[3]);
            _setEffectTexture(gd,_nz,"Content//"+ textures_list[0]+"//"+ textures_list[4]);
            _setEffectTexture(gd,_ny,"Content//"+ textures_list[0]+"//"+ textures_list[5]);
            _setEffectTexture(gd,_nz,"Content//"+ textures_list[0]+"//"+ textures_list[6]);
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
                foreach(BasicEffect effect in mesh.Effects)
                {
                    effect.View = view.Value;
                    effect.Projection = projection.Value;
                    effect.World = t;
                }
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
                NX.Dispose();
                NY.Dispose();
                NZ.Dispose();
                PX.Dispose();
                PY.Dispose();
                PZ.Dispose();
            }
            _disposed = true;
        }
    }
}
