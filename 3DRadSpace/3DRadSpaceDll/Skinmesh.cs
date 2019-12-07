﻿using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Class for drawing 3D object.
    /// </summary>
    public class Skinmesh : GameObject, IEffectFog
    {
        /// <summary>
        /// Skinmesh constructor.
        /// </summary>
        /// <param name="name">Object's name.</param>
        /// <param name="active">Checks if the skinmesh will get drawn.</param>
        /// <param name="resource">Resource name, from the 'root'/Content/ without the xnb extension.</param>
        /// <param name="position">Object position</param>
        /// <param name="rotation">Object rotation in Euler Angles measured in radians.</param>
        /// <param name="scale">Object scale. (1,1,1) is default.</param>
        /// <param name="fog_affected">Allows or not fogs.</param>
        public Skinmesh(string name, bool active, string resource, Vector3 position = default,Vector3 rotation = default,Vector3 scale = default,bool fog_affected= true)
        {
            Name = name;
            Enabled = active;
            Resource = resource;
            Position = position;
            Rotation = rotation;
            Scale = scale;
            if (Scale == default) Scale = new Vector3(1, 1, 1);
            FogEnabled = fog_affected;
            if(FogEnabled)
            {
                FogColor = new Vector3(255,255,255);
                FogEnd = int.MaxValue;
                FogStart = int.MaxValue;
            }
        }

        /// <summary>
        /// The Model itself.
        /// </summary>
        public Model Model { get; private set; }
        /// <summary>
        /// Fog effect color. From IEffectFog.
        /// </summary>
        public Vector3 FogColor { get; set; }
        /// <summary>
        /// Checks if the Skinmesh allows fogs.
        /// </summary>
        public bool FogEnabled { get; set; }
        /// <summary>
        /// Fog end distance.
        /// </summary>
        public float FogEnd { get; set; }
        /// <summary>
        /// Fog start distance.
        /// </summary>
        public float FogStart { get; set; }

        /// <summary>
        /// Model scale. Default is (1,1,1).
        /// </summary>
        public Vector3 Scale
        {
            get { return _scale;  }
            set
            {
                if (value == Vector3.Zero) throw new ArgumentException("Skinmesh.Scale", "Zero scales are not supported.");
                else _scale = value;
            }
        }
        Vector3 _scale;

        /// <summary>
        /// Loads the model. Uses Monogame's content pipeline.
        /// </summary>
        /// <param name="content">ContentManager from the game instance.</param>
        public override void Load(ContentManager content)
        {
            Model = content.Load<Model>(Resource);
            base.Load(content);
        }
        /// <summary>
        /// Draws the mesh.
        /// </summary>
        /// <param name="spriteBatch">Not used.</param>
        /// <param name="view">Necessary for model drawing.</param>
        /// <param name="projection">Necessary for model drawing.</param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (!Enabled) return;
            foreach(ModelMesh mesh in Model.Meshes)
            {
                foreach(BasicEffect effect in mesh.Effects)
                {
                    effect.View = (Matrix)view;
                    effect.Projection = (Matrix)projection;
                    effect.World = Matrix.CreateScale(_scale) * Matrix.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z) * Matrix.CreateTranslation(Position);
                    effect.FogEnabled = FogEnabled;
                    effect.FogColor = FogColor;
                    effect.FogStart = FogStart;
                    effect.FogEnd = FogEnd;
                }
                mesh.Draw();
            }
            base.Draw(spriteBatch, view, projection);
        }
        /// <summary>
        /// Draws the mesh in the editor. The only difference from Draw() is the missing condition.
        /// </summary>
        /// <param name="spriteBatch">Not used.</param>
        /// <param name="view">View Matrix.</param>
        /// <param name="projection">Projection Matrix</param>
        public override void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            foreach (ModelMesh mesh in Model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.View = (Matrix)view;
                    effect.Projection = (Matrix)projection;
                    effect.World = Matrix.CreateScale(_scale) * Matrix.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z) * Matrix.CreateTranslation(Position);
                }
                mesh.Draw();
            }
            base.EditorDraw(spriteBatch, view, projection);
        }
    }
}