using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    namespace Physics
    {
        /// <summary>
        /// 
        /// </summary>
        public enum ForceType:byte
        {
            /// <summary>
            /// 
            /// </summary>
            Undefined=0,
            /// <summary>
            /// 
            /// </summary>
            Acceleration,
            /// <summary>
            /// 
            /// </summary>
            Spin,
        }
    }
    /// <summary>
    /// 
    /// </summary>
    public class Force : BaseGameObject
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="direction"></param>
        /// <param name="t"></param>
        /// <param name="power"></param>
        /// <param name="time_interval"></param>
        /// <param name="objects"></param>
        public Force(string name="Force",Vector3 direction=default,Physics.ForceType t=Physics.ForceType.Undefined,float power=0,float time_interval=0,int[] objects=null)
        {
            Name = name;
            RotationEuler = direction;
            TimeInterval = time_interval;
            ForceType = t;
            Intensity = power;
            Behiavours = new List<BehiavourStruct>(5);
            for(int i = 0; i < objects.Length; i++)
                Behiavours.Add(new BehiavourStruct(objects[i], 0)); //Linked objects are never ignored.
        }
        /// <summary>
        /// 
        /// </summary>
        public Physics.ForceType ForceType;
        /// <summary>
        /// 
        /// </summary>
        public float TimeInterval;
        /// <summary>
        /// 
        /// </summary>
        public float Intensity;
        /// <summary>
        /// 
        /// </summary>
        public bool IsBeingApplied
        {
            get
            {
                return _forcetime > 0;
            }
        }
        float _forcetime;

        /// <summary>
        /// Activates the force.
        /// </summary>
        public override void Trigger()
        {
            _forcetime = TimeInterval;
        }
        /// <summary>
        /// Activates the force with a custom time interval.
        /// </summary>
        /// <param name="custom_time_interval"></param>
        public void Trigger(float custom_time_interval)
        {
            _forcetime = custom_time_interval;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="input"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(ref MouseState input, ref KeyboardState keyboard, GameTime time)
        {
            if(_forcetime > 0)
            {
                _forcetime -= (float)time.ElapsedGameTime.TotalSeconds;
                for(int i =0; i < Behiavours.Count;i++)
                {
                    if(CurrentProject.GameObjects[Behiavours[i].ObjectID] is IPhysicsObject phobj)
                    {
                        phobj.ApplyForce(RotationEuler, ForceType, Intensity);
                    }
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
            //TODO: DRAW AN ARROW?? Yes, no? idk
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
            Vector3 dir = ByteCodeParser.GetVector3(buff,ref position);
            Physics.ForceType ft = (Physics.ForceType)ByteCodeParser.GetByte(buff,ref position);
            Vector2 v1 = ByteCodeParser.GetVector2(buff, ref position);
            int objc = ByteCodeParser.GetInt(buff, ref position);

            int[] objs = new int[objc];
            for(int i =0; i < objc; )
            {
                objs[i] = ByteCodeParser.GetInt(buff, ref position);
            }
            result = new Force(name,dir,ft,v1.X,v1.Y,objs);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        public override void SaveF(List<byte> buff)
        {
            ByteCodeParser.SetString(buff, Name);
            ByteCodeParser.SetVector3(buff, RotationEuler);
            ByteCodeParser.SetByte(buff, (byte)ForceType);
            ByteCodeParser.SetVector2(buff, new Vector2(Intensity, TimeInterval));

            int l = Behiavours.Count;
            ByteCodeParser.SetInt(buff, l);

            for(int i =0; i < l;i++)
            {
                ByteCodeParser.SetInt(buff, Behiavours[i].ObjectID);
            }
        }
    }
}
