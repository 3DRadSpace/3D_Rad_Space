using System;
namespace _3DRadSpaceDll
{
    /// <summary>
    /// Base 3DRadSpace object class
    /// </summary>
    public class GObject
    {
        /// <summary>
        /// The type name of the object. Used to identify the object
        /// </summary>
        string type;
        /// <summary>
        /// Common setting in all objects.
        /// </summary>
        public bool is_activated;
        /// <summary>
        /// The settings of the object stored in a string array.
        /// </summary>
        public string[] properties;
        /// <summary>
        /// Creates an object (ANY TYPE). Returns the base object class.
        /// </summary>
        /// <param name="args">The object string array.</param>
        /// <returns></returns>
        public static GObject CreateObject(string[] args)
        {
            GObject returned = new GObject();
            returned.type = args[0];
            returned.is_activated = Convert.ToBoolean(args[1]);
            returned.properties = new string[args.Length - 2];
            for (int i = 2; i < args.Length; i++)
            {
                returned.properties[i] = args[i];
            }
            return returned;
        }
        /// <summary>
        /// Called every time when the game updates it's world.
        /// </summary>
        protected virtual void Object_Update()
        {
            return;
        }
        /// <summary>
        /// Called before a frame finish drawing.
        /// </summary>
        protected virtual void Object_Draw()
        {
            return;
        }
    }
    /// <summary>
    /// Camera Object Class. Based on the base 3DRadSpace object class.
    /// </summary>
    public class Camera : GObject
    {
        protected override void Object_Draw()
        {

        }
        protected override void Object_Update()
        {

        }
    }
    /// <summary>
    /// 3DRadSpace script interpeter. Use this when script objects are implied.
    /// </summary>
    public class ScriptInterpeter
    {
        /// <summary>
        /// Checks if a script has a error in it's code.
        /// </summary>
        /// <param name="script"></param>
        public static void Debug(string script)
        {

        }
        /// <summary>
        /// Executes a script.
        /// </summary>
        /// <param name="script"></param>
        public static void Run(string script)
        {

        }
    }
}

