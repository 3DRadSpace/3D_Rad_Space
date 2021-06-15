using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Lib3DRadSpace_DX
{
    public delegate void UpdateLoopEvent(float dt, MouseState mouse, KeyboardState keyboard);
    /// <summary>
    /// Represents an objects that raises events.
    /// </summary>
    public interface IEventObject
    {
        /// <summary>
        /// 
        /// </summary>
        UpdateLoopEvent Event { get; }

        ScriptBlocks.Opcode[] EventsOpcodes { get; }
    }
}
