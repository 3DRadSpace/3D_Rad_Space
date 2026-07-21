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
    public struct BehiavourStruct
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="beh"></param>
        public BehiavourStruct(int id,int beh)
        {
            ObjectID = id;
            Behiavour = beh;
        }
        /// <summary>
        /// 
        /// </summary>
        public int ObjectID;
        /// <summary>
        /// 
        /// </summary>
        public int Behiavour;

        /// <summary>
        /// Returns a string representation used in UI.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return "[" + ObjectID + "]" + CurrentProject.GameObjects[ObjectID].Name;
        }
        /// <summary>
        /// Returns a string representation used in UI.
        /// </summary>
        /// <param name="f">Function containing a switch-case for all the Behiavour ID names.</param>
        /// <returns>A string designed for UI interfaces.</returns>
        public string ToString(Func<int,string> f)
        {
            return "[" + ObjectID + "]" + CurrentProject.GameObjects[ObjectID].Name + "(" + f(Behiavour) + ")[" + Behiavour + "]";
        }
    }
}
