using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// This is the class containing replicas of the old functions just like in the original 3D Rad engine.
    /// </summary>
    public static class Scripting
    {
        /*
         *  OBJECT FUNCTIONS
         */

        /// <summary>
        /// Starts or triggers the specified object.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectStart(int id)
        {
            CurrentProject.GameObjects[id].Trigger();
        }
        /// <summary>
        /// Stops the specified object from executing it's update logic loop.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectStop(int id)
        {
            CurrentProject.GameObjects[id].Enabled = false;
        }
        /// <summary>
        /// Switch the specified object (starts if stopped, and vice-versa). This affects the updating cycle.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectSwitch(int id)
        {
            CurrentProject.GameObjects[id].Enabled = !(CurrentProject.GameObjects[id].Enabled);
        }
        /// <summary>
        /// Shows the specified object by allowing it in the draw cycle.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectShow(int id)
        {
            CurrentProject.GameObjects[id].Visible = true;
        }
        /// <summary>
        /// Hides the object, by stopping it from being draw in the drawing cycle.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectHide(int id)
        {
            CurrentProject.GameObjects[id].Visible = false;
        }
        /// <summary>
        /// Switches the object's visibility
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectShowHideSwitch(int id)
        {
            CurrentProject.GameObjects[id].Visible = !CurrentProject.GameObjects[id].Visible;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectReset(int id)
        {
            //???
            //How the heck are we even going to store the initial object values? Who wants an exta copy of an array?
        }
    }
}
