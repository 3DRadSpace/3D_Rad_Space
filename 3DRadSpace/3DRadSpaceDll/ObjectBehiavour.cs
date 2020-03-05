using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Specifies object relationships with other ones.
    /// </summary>
    public struct ObjectBehiavour
    {
        /// <summary>
        /// Object Identifier for the 'child' object
        /// </summary>
        public int ObjectID;
        /// <summary>
        /// Behiavour identifier. 0 is always default.
        /// </summary>
        public int BehiavourID;
        /// <summary>
        /// Default constructor.
        /// </summary>
        /// <param name="ID">Object identifier</param>
        /// <param name="beh">Behiavour ID.</param>
        public ObjectBehiavour(int ID=-1, int beh = 0)
        {
            ObjectID = ID;
            BehiavourID = beh;
        }
    }
}
