using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// A interface that should be used when creating custom object
    /// </summary>
    public interface ICustomGameObject
    {
        /// <summary>
        /// Returns a string representing the object's data that will be saved in a text-format project.
        /// <para>The general format is:</para>
        /// <para>string(OBJECT_TYPE_STRING_ID) string(NAME) bool(ENABLED) ...etc</para>
        /// </summary>
        string SaveText();
        /// <summary>
        /// Returns the custom object from the specified argument.
        /// </summary>
        /// <param name="text">A tokenised string array containing the data as strings.</param>
        /// <returns>The general format is:
        /// <para>string(OBJECT_TYPE_STRING_ID) string(NAME) bool(ENABLED) ...etc</para></returns>
        object LoadText(string[] text);
        /// <summary>
        /// Returns a byte array representing the object.
        /// </summary>
        /// <returns>Byte array representing the object</returns>
        byte[] SaveBinary();
        /// <summary>
        /// Created the object from the specified buffer.
        /// </summary>
        /// <param name="b">Buffer representing the entire project.</param>
        /// <param name="offset">Buffer offset</param>
        void LoadBinary(byte[] b, string offset);
    }
}
