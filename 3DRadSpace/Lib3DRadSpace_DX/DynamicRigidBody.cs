using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BEPUphysics;
using BEPUphysics.CollisionRuleManagement;
using BEPUphysics.Entities;
using Lib3DRadSpace_DX.Physics;
using Microsoft.Xna.Framework;

using XNAVector3 = Microsoft.Xna.Framework.Vector3;
using Vector3 = BEPUutilities.Vector3;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Represents a solid shape approximated with primitive objects like cubes and spheres.
    /// </summary>
    public class DynamicRigidBody : BaseGameObject, IPhysicsObject
    {
        /// <summary>
        /// Represents the main dynamic rigidbody constructor.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="visible"></param>
        /// <param name="pos"></param>
        /// <param name="rot"></param>
        /// <param name="scal"></param>
        /// <param name="primitives"></param>
        public DynamicRigidBody(string name, bool enabled, bool visible, XNAVector3 pos, XNAVector3 rot, XNAVector3 scal, Physics.PhysicsPrimitive[] primitives)
        {
            Name = name;
            _enabled = enabled;
            Visible = visible;
            Position = pos;
            RotationEuler = rot;
            Scale = scal;
            Entities = new List<Entity>(primitives.Length);
            for(int i = 0; i < primitives.Length; i++)
            {
                switch(primitives[i].Type)
                {
                    case PhysicsPrimitiveType.Box:
                    {
                        //Entities.Add(new Entity(new BEPUphysics.CollisionShapes.ConvexShapes.BoxShape()))
                        break;
                    }
                }
            }
        }

        List<Entity> Entities;

        /// <summary>
        /// Toggles physics of this object.
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
                else if(_enabled) disablecollision();

                _enabled = value;
            }
        }
        void enablecollision()
        {
            for(int i = 0; i < Entities.Count; i++)
            {
                Entities[i].CollisionInformation.CollisionRules.Personal = CollisionRule.Normal;
            }
        }
        void disablecollision()
        {
            for(int i = 0; i < Entities.Count; i++)
            {
                Entities[i].CollisionInformation.CollisionRules.Personal = CollisionRule.Normal;
            }
        }
        bool _enabled;

        /// <summary>
        /// Adds the primitives into the physics simulation.
        /// </summary>
        /// <param name="space"></param>
        public override void PhysicsInitialize(Space space)
        {
            for(int i = 0; i < Entities.Count; i++)
            {
                Entities[i].Position = BEPU2XNA.BEPUVector(Position);
                Entities[i].Orientation = BEPU2XNA.BEPUQuaternion(Quaternion.CreateFromYawPitchRoll(RotationEuler.Y, RotationEuler.X, RotationEuler.Z));
                space.Add(Entities[i]);
            }
        }

        /// <summary>
        /// Draws the collision primitives with a transparent red color.
        /// </summary>
        /// <param name="time"></param>
        /// <param name="frustrum"></param>
        /// <param name="view"></param>
        /// <param name="projection"></param>
        public override void EditorDraw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            //TOOD: Use primitive meshes.
            //TFW they arent there
        }
        /// <summary>
        /// Applies a force to the body.
        /// </summary>
        /// <param name="dir">Force direction. A normalized vector.</param>
        /// <param name="t">The force type.</param>
        /// <param name="intensity">Force intensity</param>
        public void ApplyForce(XNAVector3 dir, ForceType t, float intensity)
        {
            for(int i = 0; i < Entities.Count; i++)
            {
                switch(t)
                {
                    case ForceType.Acceleration:
                    {
                        Vector3 v = BEPU2XNA.BEPUVector(dir) * intensity;
                        Entities[i].ApplyLinearImpulse(ref v);
                        break;
                    }
                    case ForceType.Spin:
                    {
                        Vector3 v = BEPU2XNA.BEPUVector(dir) * intensity;
                        Entities[i].ApplyAngularImpulse(ref v);
                        break;
                    }
                    default: return;
                }
            }
        }
    }
}
