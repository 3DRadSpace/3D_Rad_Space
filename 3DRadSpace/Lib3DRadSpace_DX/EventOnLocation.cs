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
    public class EventOnLocation : BaseGameObject, IEventObject
    {
        /// <summary>
        /// 
        /// </summary>
        public UpdateLoopEvent Event { get; }
        /// <summary>
        /// 
        /// </summary>
        public ScriptBlocks.Opcode[] EventsOpcodes { get; }

        public EventOnLocation()
        {

        }
    }
}
