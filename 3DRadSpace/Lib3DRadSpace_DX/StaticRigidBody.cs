using System;
using BEPUphysics;
using BEPUphysics.BroadPhaseEntries;
using BEPUutilities;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

using XNAVector3 = Microsoft.Xna.Framework.Vector3;
using Quaternion = BEPUutilities.Quaternion;
using Matrix = Microsoft.Xna.Framework.Matrix;
using ContainmentType = Microsoft.Xna.Framework.ContainmentType;
using BEPUphysics.CollisionRuleManagement;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Represents a static rigidbody generated from a mesh.
    /// </summary>
    public class StaticRigidBody : BaseGameObject
    {
        /// <summary>
        /// Represents the Rigidbody constructor.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="visible"></param>
        /// <param name="translation"></param>
        /// <param name="rotation_euler"></param>
        /// <param name="initial_scale"></param>
        /// <param name="modelasset"></param>
        public StaticRigidBody(string name,bool enabled,bool visible, XNAVector3 translation, XNAVector3 rotation_euler, XNAVector3 initial_scale,string modelasset)
        {
            Name = name;
            _enabled = enabled;
            Visible = visible;
            _pos = translation;
            Asset = modelasset;
            _euler_rot = rotation_euler;
            _scal = initial_scale;
        }

        Model _model;

        /// <summary>
        /// 
        /// </summary>
        public new bool Enabled
        {
            get
            {
                return _enabled;
            }
            set
            {
                if(value)
                {
                    if(!_enabled) enablecollision();
                }
                else
                {
                    if(_enabled) disablecollision();
                }
                _enabled = value;
            }
        }
        bool _enabled;

        void enablecollision()
        {
            for(int i =0; i < collisionmap.Length;i++)
            {
                collisionmap[i].CollisionRules.Personal = CollisionRule.Normal;
            }
        }
        void disablecollision()
        {
            for(int i = 0; i < collisionmap.Length; i++)
            {
                collisionmap[i].CollisionRules.Personal = CollisionRule.NoSolver;
            }
        }
        /// <summary>
        /// Represents the position of the static rigidbody. CAN ONLY BE SET BEFORE INITIALIZING THE PHYSICS.
        /// </summary>
        public new XNAVector3 Position
        {
            get
            {
                return _pos;
            }
        }
        XNAVector3 _pos;

        /// <summary>
        /// Represents the rotation of the static rigidbody.
        /// </summary>
        public new XNAVector3 RotationEuler
        {
            get
            {
                return _euler_rot;
            }
        }
        XNAVector3 _euler_rot;

        /// <summary>
        /// Represents the initial scale of the collision map.
        /// </summary>
        public new XNAVector3 Scale
        {
            get
            {
                return _scal;
            }
        }
        XNAVector3 _scal;

        /// <summary>
        /// 
        /// </summary>
        public new Matrix World
        {
            get
            {
                return Matrix.CreateScale(_scal) * Matrix.CreateFromYawPitchRoll(_euler_rot.Y, _euler_rot.X, _euler_rot.Z) * Matrix.CreateTranslation(_pos);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            _model = content.Load<Model>(Asset);
        }

        StaticMesh[] collisionmap;

        /// <summary>
        /// Generates the collision mesh
        /// </summary>
        /// <param name="space"></param>
        public override void PhysicsInitialize(Space space)
        {
            collisionmap = BEPU2XNA.GenerateCollisionMesh(_model);
            for(int i =0; i < collisionmap.Length;i++)
            {
                collisionmap[i].WorldTransform = new AffineTransform(
                    BEPU2XNA.BEPUVector(_scal),
                    Quaternion.CreateFromYawPitchRoll(_euler_rot.Y, _euler_rot.X, _euler_rot.Z),
                    BEPU2XNA.BEPUVector(_pos)); 

                space.Add(collisionmap[i]);
            }
        }
        /// <summary>
        /// Draws the collision mesh with a red transparent color.
        /// </summary>
        /// <param name="time"></param>
        /// <param name="frustrum"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void EditorDraw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            if(!Visible) return;
            bool candraw = false;
            for(int i = 0; i < _model.Meshes.Count && !candraw; i++)
            {
                if(frustrum.Contains(_model.Meshes[i].BoundingSphere) != ContainmentType.Disjoint)
                    candraw = true;
            }
            if(candraw)
            {
                for(int i = 0; i < _model.Meshes.Count; i++)
                {
                    for(int j = 0; j < _model.Meshes[i].MeshParts.Count; j++)
                    {
                        CurrentProject.BasicColorShader.DrawModelPart(_model.Meshes[i].MeshParts[j], World, view, projection);
                    }
                }
            }
        }
        /// <summary>
        /// Draws the collision model
        /// </summary>
        /// <param name="time"></param>
        /// <param name="frustrum"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            if(!Visible) return;
            for(int i = 0; i < _model.Meshes.Count; i++)
            {
                if(frustrum.Contains(_model.Meshes[i].BoundingSphere) != ContainmentType.Disjoint)
                {
                    _model.Draw(World, view, projection);
                    break;
                }
            }
        }
    }
}
