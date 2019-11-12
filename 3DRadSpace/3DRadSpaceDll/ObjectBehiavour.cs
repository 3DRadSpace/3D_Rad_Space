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
    public class ObjectBehiavour
    {
        /// <summary>
        /// Object Identifier for the 'child' object
        /// </summary>
        public int ObjectID { get; private set; }
        /// <summary>
        /// Behiavour identifier. 0 is always default.
        /// </summary>
        public int BehiavourID { get; set; }
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="ID">Object identifier</param>
        /// <param name="beh"></param>
        public ObjectBehiavour(int ID, int beh)
        {
            ObjectID = ID;
            BehiavourID = beh;
        }
        /// <summary>
        /// Constructor with minimal arguments.
        /// </summary>
        /// <param name="ID">'Child' object identifier.</param>
        public ObjectBehiavour(int ID)
        {
            ObjectID = ID;
            BehiavourID = 0;
        }
    }
}
