using Microsoft.Xna.Framework;
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
        public Group(string name,bool enabled,Vector3 pos,Vector3 rot,List<int> objects)
        {
            Behiavours = new List<BehiavourStruct>(objects.Count);
            for(int i =0; i < objects.Count;i++)
            {
                Behiavours[i] = new BehiavourStruct(objects[i],1);
            }
            _prev = pos;
            Position = pos;
            RotationEuler = rot;
            _prev_rot = rot;
        }
        Vector3 _prev;
        Vector3 _prev_rot;
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
            }
            _prev = Position;
        }
    }
}
