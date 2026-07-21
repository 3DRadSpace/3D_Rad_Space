using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

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


        /// <summary>
        /// 
        /// </summary>
        /// <param name="n"></param>
        /// <param name="e"></param>
        /// <param name="p"></param>
        /// <param name="s"></param>
        /// <param name="objs"></param>
        /// <param name="events"></param>
        public EventOnLocation(string n,bool e,Vector3 p,Vector3 s,int[] objs,ScriptBlocks.Opcode[] events)
        {
            Name = n;
            Enabled = e;
            Position = p;
            Scale = s;
            EventsOpcodes = events;
        }
        public override void Update(ref MouseState input, ref KeyboardState keyboard, GameTime time)
        {
            
        }
    }
}
