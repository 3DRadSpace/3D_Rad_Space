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
    /// Visual script compiler, debugger and functions.
    /// </summary>
    public class VisualScript
    {
        /// <summary>
        /// The script data.
        /// </summary>
        public object[] data;
        /// <summary>
        /// Variables in the project.
        /// </summary>
        public static object[] variables = new object[_3DRadSpaceGame.MAX_VARIABLES];
        /// <summary>
        /// Global variables. Can be used in the entire game.
        /// </summary>
        public static object[] GLOBALVARIABLES = new object[_3DRadSpaceGame.MAX_VARIABLES];
        /// <summary>
        /// Script constructor
        /// </summary>
        /// <param name="script">File string array returned by File.ReadAllLines()</param>
        public VisualScript(string[] script)
        {
            data = script;
        }
        /// <summary>
        /// Checks a script for errors.
        /// </summary>
        public void Debug()
        {
            for(int i=0; i < data.Length; i++)
            {
                string[] line = data.ToString().Split(' ');
                VisualScriptOpcode opcode = (VisualScriptOpcode)Convert.ToInt32(line[0]);
                if (requredparams(opcode) == line.Length - 1)
                {
                    continue;
                }
                else throw new InvalidNumberOfParams("OPCODE:" + opcode + " params:" + (line.Length - 1) + " expected params:" + requredparams(opcode)); 
            }
        }
        /// <summary>
        /// Executes a script.
        /// </summary>
        public void Run()
        {
        }
        int requredparams(VisualScriptOpcode a)
        {
            if (a == VisualScriptOpcode.NOP) return 0;
            if (a > VisualScriptOpcode.NOP && a < VisualScriptOpcode.var) return 1;
            else return -1;
        }
    }
    /// <summary>
    /// Contains the function numeric IDs.
    /// </summary>
    public enum VisualScriptOpcode
    {
        /// <summary>
        /// Does nothing. No parameters
        /// </summary>
        NOP = 0,
        /// <summary>
        /// Starts an object. Parameters: object handle as int
        /// </summary>
        OBJStart = 1,
        /// <summary>
        /// Stops an object. Parameters: object handle as int
        /// </summary>
        OBJStop = 2,
        /// <summary>
        /// Shows an object. Parameters: object handle as int
        /// </summary>
        OBJShow = 3,
        /// <summary>
        /// Hides an object. Parameters: object handle as int
        /// </summary>
        OBJHide = 4,
        /// <summary>
        /// Removes an object from the array that contains the objects. Parameters: object handle as int
        /// </summary>
        OBJDestroy =5,
        /// <summary>
        /// Reloads the resource of the object. Parameters: string resource, int obj handle
        /// </summary>
        OBJReload = 6,
        /// <summary>
        /// Saves a variable into the variables array. int handle,string name, object value
        /// </summary>
        var = 7, 
        /// <summary>
        /// Increases the variable by the specified number. Parameters : variable, value 
        /// </summary>
        varoperatorplus = 8,
        /// <summary>
        /// Decreases the variable by the specified number. Parameters : variable, value
        /// </summary>
        varoperatorminus = 9,
        /// <summary>
        /// Multiplies the variable by the specified number. Parameters : variable, value
        /// </summary>
        varoperatormultiply = 10,
        /// <summary>
        /// Divides the variable by the specified number. Parameters : variable, value
        /// </summary>
        varoperatordivide = 11,
        /// <summary>
        /// Gets the modulo of the 2 specified numbers. Parameters : variable, value
        /// </summary>
        varoperatormodulo = 12,
       /// <summary>
       /// Removes an variable from the array. Parameters: variable handle
       /// </summary>
        vardelete = 13,
        /// <summary>
        /// Moves an object to an location. Parameters: object handle, float x, float y,float z, int incr
        /// </summary>
        OBJMoveTo = 14,
        /// <summary>
        /// Rotates the object using euler angles. Parameters: object handle, float x, float y, float z, int incr
        /// </summary>
        OBJRotate = 15,
        /// <summary>
        /// Sets an property specific to the object. Parameters: object handle, int property, object value
        /// </summary>
        OBJPropertySet = 16,
        /// <summary>
        /// Stops running the script.
        /// </summary>
        ScriptStop = 17,
        
    };
    enum VisualScriptType
    {
        Int = 0,
        Float = 1,
        String = 2,
        ArrayPointer = 3,
        Object = 4,
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
