using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using System.IO;


namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Represents a 3D model. No animation support (yet, I hope)
    /// </summary>
    public class Skinmesh : BaseGameObject
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="visible"></param>
        /// <param name="pos"></param>
        /// <param name="rotation"></param>
        /// <param name="scale"></param>
        /// <param name="t_shaders"></param>
        /// <param name="effects"></param>
        public Skinmesh(string name,bool visible,Vector3 pos,Quaternion rotation, Vector3 scale,List<Shaders.IShader> t_shaders,List<Effect> effects)
        {
            Name = name;
            Visible = visible;
            Position = pos;
            Rotation = rotation;
            Scale = scale;
            Shaders = t_shaders;
            Effects = effects;
        }
        /// <summary>
        /// Represents the 3D model itself. (Containts the index and vertex buffer).
        /// </summary>
        public Model Model;
        /// <summary>
        /// Contains a list of shaders to be atributted to each mesh part (textured mesh)
        /// </summary>
        public List<Shaders.IShader> Shaders;
        /// <summary>
        /// List of effects to be used with the mesh parts.
        /// </summary>
        public List<Effect> Effects;
        /// <summary>
        /// Draws the 3D model using the specified shaders.
        /// </summary>
        /// <param name="time">Not used.</param>
        /// <param name="frustrum">Bounding frustrum used to optimise the drawing by checking if the model can be seen by the camera.</param>
        /// <param name="view">View matrix.</param>
        /// <param name="projection">Projection matrix</param>
        public override void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            if (Model == null) return;
            if (!Visible) return;
            bool canDraw = false;
            for(int i =0; i < Model.Meshes.Count;i++)
            {
                if(frustrum.Contains(Model.Meshes[i].BoundingSphere) == ContainmentType.Contains)
                {
                    canDraw = true;
                    break;
                }
            }
            if(canDraw)
            {
                for (int i = 0; i < Model.Meshes.Count; i++)
                {
                    for (int j = 0; j < Shaders.Count; j++)
                    {
                        Shaders[j].DrawModelPart(Effects[j], Model.Meshes[i].MeshParts[j], World, view, projection);
                    }
                }
            }
        }
        /// <summary>
        /// Draws the model for the editor. This is the same as Draw() since there's no difference.
        /// </summary>
        /// <param name="time">Not used</param>
        /// <param name="frustrum">Used to optimise the drawing.</param>
        /// <param name="view">View matrix.</param>
        /// <param name="projection">Projection matrix.</param>
        public override void EditorDraw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            Draw(time, frustrum,ref view,ref projection);
        }
        Texture2D[] _Textures;
        /// <summary>
        /// Loads the model by using the content pipeline.
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            //load shader list and parameters
            string[] details = File.ReadAllLines(Asset);

            Shaders = new List<Shaders.IShader>(details.Length - 1);
            for(int i =1; i < details.Length; i++)
            {
                string[] shader_info = details[i].Split(' ');
                for(int j =0; j < shader_info.Length;j++)
                {
                    switch(shader_info[j])
                    {
                        case "default":
                            break;
                    }
                }
            }

            //load model.
            Model = content.Load<Model>(details[0]);

            //make model compatible with other shaders.

            //count number of meshparts.
            int c = 0;
            for(int i =0; i < Model.Meshes.Count;i++)
            {
                for(int j =0; j < Model.Meshes[i].MeshParts.Count;j++)
                {
                    c++;
                }
            }
            //allocate basic textures.
            _Textures = new Texture2D[c];
            //copy textures.
            for(int i = 0; i < Model.Meshes.Count;i++)
            {
                for(int j =0; j < Model.Meshes[i].MeshParts.Count;j++)
                {
                    BasicEffect eff = (BasicEffect)Model.Meshes[i].MeshParts[j].Effect;
                    if(eff.TextureEnabled)
                    {
                        _Textures[i] = eff.Texture;
                    }
                    else _Textures[i] = null;
                }
            }
        }
    }
}
