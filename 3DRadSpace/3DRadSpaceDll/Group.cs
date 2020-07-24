using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Represents a group of objects. Only use as a Editor helper object. It's no use in any standalone project.
    /// </summary>
    public class Group : GameObject
    {
        /// <summary>
        /// Complete group object constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="objs">List ob objects</param>
        public Group(string name, IEnumerable<int> objs)
        {
            Name = name;
            SelectedObjects = new List<int>(objs.Count());
            SelectedObjects.AddRange(objs);
        }
        /// <summary>
        /// Empty Group constructor.
        /// </summary>
        public Group()
        {
            Name = "Group";
            SelectedObjects = new List<int>();
        }

        /// <summary>
        /// Applies a translation to the objects.
        /// </summary>
        /// <param name="translation"></param>
        public void ApplyTranslation(Vector3 translation)
        {
            for(int i =0; i < SelectedObjects.Count;i++)
            {
                Main.GameObjects[SelectedObjects[i]].Position += translation;
            }
        }
        /// <summary>
        /// Applies a euler angle rotation to the group objects.
        /// </summary>
        /// <param name="euler"></param>
        public void ApplyRotation(Vector3 euler)
        {
            for (int i = 0; i < SelectedObjects.Count; i++)
            {
                Main.GameObjects[SelectedObjects[i]].Rotation += euler;
            }
        }
        /// <summary>
        /// Used only in the editor.
        /// </summary>
        /// <param name="spriteBatch">not used</param>
        /// <param name="view">view matrix</param>
        /// <param name="projection">projection matrix</param>
        public override void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {

            base.EditorDraw(spriteBatch, view, projection);
        }
        public static Model Marker;
    }
}
