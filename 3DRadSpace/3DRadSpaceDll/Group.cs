using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Represents a group of objects.
    /// </summary>
    public class Group : GameObject
    {
        /// <summary>
        /// Complete group object constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="enabled">Checks if the object is enabled</param>
        /// <param name="objs">List ob objects</param>
        public Group(string name,bool enabled, IEnumerable<int> objs)
        {
            Name = name;
            Enabled = enabled;
            ObjectsInList = new List<int>(objs.Count());
            ObjectsInList.AddRange(objs);
        }
        /// <summary>
        /// Represents a list of the linked objects.
        /// </summary>
        public List<int> ObjectsInList;

        /// <summary>
        /// Applies a translation to the objects.
        /// </summary>
        /// <param name="translation"></param>
        public void ApplyTranslation(Vector3 translation)
        {
            for(int i =0; i < ObjectsInList.Count;i++)
            {
                Game.GameObjects[ObjectsInList[i]].Position += translation;
            }
        }
        /// <summary>
        /// Applies a euler angle rotation to the group objects.
        /// </summary>
        /// <param name="euler"></param>
        public void ApplyRotation(Vector3 euler)
        {
            for (int i = 0; i < ObjectsInList.Count; i++)
            {
                Game.GameObjects[ObjectsInList[i]].Rotation += euler;
            }
        }
        
    }
}
