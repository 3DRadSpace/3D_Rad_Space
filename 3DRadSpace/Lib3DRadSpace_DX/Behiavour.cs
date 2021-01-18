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
    }
}
