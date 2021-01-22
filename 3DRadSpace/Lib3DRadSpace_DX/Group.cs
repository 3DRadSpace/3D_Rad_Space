using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// 
    /// </summary>
    public class Group : BaseGameObject
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="objects"></param>
        /// <param name="pos"></param>
        /// <param name="rot"></param>
        /// <param name="scale"></param>
        public Group(string name,bool enabled,Vector3 pos,Vector3 rot,Vector3 scale,List<int> objects)
        {
            Name = name;
            Enabled = enabled;
            Behiavours = new List<BehiavourStruct>(objects.Count);
            _scales = new Vector3[objects.Count];
            for(int i =0; i < objects.Count;i++)
            {
                Behiavours[i] = new BehiavourStruct(objects[i],1);
            }
            _prev = pos;
            Position = pos;
            RotationEuler = rot;
            _prev_rot = rot;
            Scale = scale;
        }
        Vector3 _prev;
        Vector3 _prev_rot;

        Vector3[] _scales;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            //Copy the scales so we prevent increasing the linked object every frame.
            for(int i =0; i < _scales.Length;i++)
            {
                _scales[i] = CurrentProject.GameObjects[Behiavours[i].ObjectID].Scale;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="input"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(ref MouseState input, ref KeyboardState keyboard, GameTime time)
        {
            for(int i=0;i< Behiavours.Count;i++)
            {
                CurrentProject.GameObjects[Behiavours[i].ObjectID].Position += _prev;
                CurrentProject.GameObjects[Behiavours[i].ObjectID].RotationEuler += _prev_rot;
                CurrentProject.GameObjects[Behiavours[i].ObjectID].Scale = Maths.MultiplyScale(_scales[i],Scale);
            }
            _prev = Position;
        }
    }
}
