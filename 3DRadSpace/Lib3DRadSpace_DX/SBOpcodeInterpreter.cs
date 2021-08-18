using Microsoft.Xna.Framework;

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
                        Scripting.iObjectStart((int)args[0]);
                        break;
                    }
                    case Opcode.StopObject:
                    {
                        Scripting.iObjectStop((int)args[0]);
                        break;
                    }
                    case Opcode.SwitchObject:
                    {
                        Scripting.iObjectSwitch((int)args[0]);
                        break;
                    }
                    case Opcode.ShowObject:
                    {
                        Scripting.iObjectShow((int)args[0]);
                        break;
                    }
                    case Opcode.HideObject:
                    {
                        Scripting.iObjectHide((int)args[0]);
                        break;
                    }
                    case Opcode.SwitchObjectVisibility:
                    {
                        Scripting.iObjectShowHideSwitch((int)args[0]);
                        break;
                    }
                    case Opcode.RunObjectOnce:
                    {
                        CurrentProject.GameObjects[(int)args[0]].RunOnce = true;
                        break;
                    }
                    case Opcode.SetPos:
                    {
                        CurrentProject.GameObjects[(int)args[0]].Position = new Vector3((float)args[1], (float)args[2], (float)args[3]);
                        break;
                    }
                    case Opcode.AddPos:
                    {
                        CurrentProject.GameObjects[(int)args[0]].Position += new Vector3((float)args[1], (float)args[2], (float)args[3]);
                        break;
                    }
                    case Opcode.SetRot:
                    {
                        CurrentProject.GameObjects[(int)args[0]].RotationEuler = new Vector3((float)args[1], (float)args[2], (float)args[3]);
                        break;
                    }
                    case Opcode.AddRot:
                    {
                        CurrentProject.GameObjects[(int)args[0]].RotationEuler += new Vector3((float)args[1], (float)args[2], (float)args[3]);
                        break;
                    }
                    case Opcode.SetScale:
                    {
                        CurrentProject.GameObjects[(int)args[0]].Scale = new Vector3((float)args[1], (float)args[2], (float)args[3]);
                        break;
                    }
                    case Opcode.AddScale:
                    {
                        CurrentProject.GameObjects[(int)args[0]].Scale += new Vector3((float)args[1], (float)args[2], (float)args[3]);
                        break;
                    }    
                    default: break;
                }    
            }
        }
    }
}
