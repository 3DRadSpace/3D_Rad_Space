using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Implements a basic Mesh model that supports color textures.
    /// </summary>
    public class Skinmesh : BaseGameObject
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name">Name of the object</param>
        /// <param name="visible">Checks if the skinmesh will get rendered</param>
        /// <param name="meshxnbfile">XNB resource file</param>
        /// <param name="p"></param>
        /// <param name="r"></param>
        /// <param name="rc"></param>
        /// <param name="s"></param>
        public Skinmesh(string name,bool visible,string meshxnbfile,Vector3 p,Vector3 r,Vector3 rc,Vector3 s)
        {
            Name = name;
            Visible = visible;
            Asset = meshxnbfile;
            Position = p;
            RotationEuler = r;
            RotationCenter = rc;
            Scale = s;
            Model = null;
        }
        /// <summary>
        /// 
        /// </summary>
        public Model Model;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            Model = content.Load<Model>(Asset);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="time"></param>
        /// <param name="frustrum"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            if(!Visible) return;
            for(int i = 0; i < Model.Meshes.Count;i++)
            {
                if(frustrum.Contains(Model.Meshes[i].BoundingSphere) != ContainmentType.Disjoint)
                {
                    Model.Draw(World, view, projection);
                    break;
                }
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="time"></param>
        /// <param name="frustrum"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void EditorDraw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            for(int i = 0; i < Model.Meshes.Count; i++)
            {
                if(frustrum.Contains(Model.Meshes[i].BoundingSphere) != ContainmentType.Disjoint)
                {
                    Model.Draw(World, view, projection);
                    break;
                }
            }
        }

        /// <summary>
        /// Checks an intersection with the Skinmesh object using a Moller Trumbore algorithm.
        /// </summary>
        /// <param name="ray"></param>
        /// <returns></returns>
        public override Vector3? RayIntersection(Ray ray)
        {
            return MollerTrumbore.RayMeshCollision(ray, Model, World);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        /// <param name="position"></param>
        /// <param name="result"></param>
        public override void LoadF(byte[] buff, ref int position, out IGameObject result)
        {
            string name = ByteCodeParser.GetString(buff,ref position);
            bool visible = ByteCodeParser.GetBool(buff, ref position);
            string asset = ByteCodeParser.GetString(buff, ref position);
            Vector3 pos = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 rot_euler = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 rot_center = ByteCodeParser.GetVector3(buff, ref position);
            Vector3 scale = ByteCodeParser.GetVector3(buff, ref position);

            result = new Skinmesh(name, visible, asset, pos, rot_euler, rot_center, scale);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        public override void SaveF(List<byte> buff)
        {
            ByteCodeParser.SetString(buff, Name);
            ByteCodeParser.SetBool(buff, Visible);
            ByteCodeParser.SetString(buff, Asset);
            ByteCodeParser.SetVector3(buff, Position);
            ByteCodeParser.SetVector3(buff, RotationEuler);
            ByteCodeParser.SetVector3(buff, RotationCenter);
            ByteCodeParser.SetVector3(buff, Scale);
        }
    }
}