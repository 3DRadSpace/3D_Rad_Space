using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    namespace ScriptBlocks
    {
        internal class OpcodeInterpreter
        {
            public static void ExecuteOpcode(Opcode op,object[] args)
            {
                switch(op)
                {
                    case Opcode.StartObject:
                    {
                        int id = (int)args[0];
                        Scripting.iObjectStart(id);
                        break;
                    }    
                }    
            }
        }
    }
}
