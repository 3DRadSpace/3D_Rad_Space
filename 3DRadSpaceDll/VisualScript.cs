using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

#pragma warning disable IDE0044
#pragma warning disable IDE1006
namespace _3DRadSpaceDll
{
    /// <summary>
    /// 3DRadSpace 'Visual Script' scripting engine.
    /// </summary>
    namespace VisualScript
    {
        /// <summary>
        /// List of opcode commands that can be used by 3D Rad Space 'Visual Script'
        /// </summary>
        public enum Opcode
        {
            /// <summary>
            /// No operation.
            /// </summary>
            NOP = 0,
            /// <summary>
            /// Executes onScriptStop() and stops execution.
            /// </summary>
            ScriptStop,
            /// <summary>
            /// Defines a variable with a value.
            /// </summary>
            Def_Var,
            /// <summary>
            /// Removes a variable.
            /// </summary>
            Undef_Var,
            /// <summary>
            /// Sets a value to a variable.
            /// </summary>
            Set_Var,
            /// <summary>
            /// Uses an variable operator.
            /// </summary>
            Operator_Var,
            /// <summary>
            /// Defines an array, needs size and 
            /// </summary>
            Def_Array,
            /// <summary>
            /// Gets an array element.
            /// </summary>
            Acess_Array,
            /// <summary>
            /// Sets an array element.
            /// </summary>
            Set_Array,
            /// <summary>
            /// Removes an array from the memory and frees memory.
            /// </summary>
            Undef_Array,
            

        }
        public class Command
        {
            public Opcode Opcode { get; private set; }
            public object[] Arguments { get; private set; }
            public Command()
            {

            }
        }
        /// <summary>
        /// Thrown when the parser finds an invalid opcode.
        /// </summary>
        [Serializable]
        public class InvalidOpcodeException : Exception
        {
            /// <summary>
            /// 
            /// </summary>
            public InvalidOpcodeException() { }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="message"></param>
            public InvalidOpcodeException(string message) : base(message) { }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="message"></param>
            /// <param name="inner"></param>
            public InvalidOpcodeException(string message, Exception inner) : base(message, inner) { }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="info"></param>
            /// <param name="context"></param>
            protected InvalidOpcodeException(
              System.Runtime.Serialization.SerializationInfo info,
              System.Runtime.Serialization.StreamingContext context) : base(info, context) { }
        }
        /// <summary>
        /// 
        /// </summary>
        [Serializable]
        public class InvalidNumberOfParams : Exception
        {
            /// <summary>
            /// 
            /// </summary>
            public InvalidNumberOfParams() { }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="message"></param>
            public InvalidNumberOfParams(string message) : base(message) { }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="message"></param>
            /// <param name="inner"></param>
            public InvalidNumberOfParams(string message, Exception inner) : base(message, inner) { }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="info"></param>
            /// <param name="context"></param>
            protected InvalidNumberOfParams(
              System.Runtime.Serialization.SerializationInfo info,
              System.Runtime.Serialization.StreamingContext context) : base(info, context) { }
        }
    }
}
